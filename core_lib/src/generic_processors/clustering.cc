#include "sct/generic_processors/clustering.hh"
#include "sct/processor.h"
#include "sct/processor_prob.hh"
#include <map>
#include "sct/generic_plane.hh"
#include "sct/ProcessorCollection.h"
#include <iostream>
#include <algorithm>


namespace sct {

  struct compare
  {
    axesName_t key;
    compare(axesName_t const &i) : key(i) { }

    bool operator()(std::pair<axesName_t, double> i){
      return (i.first == key);
    }
  };


  bool is_close(const std::vector<double> & ax_buff, double newHit, double cutOff) {
    for (const auto& a : ax_buff) {
      if (std::abs(a - newHit) > cutOff) {
        return false;
      }
    }
    return true;
  }
  class cluster{
  public:
    

    std::map<axesName_t, std::vector<double> > m_buffer;

    
    std::vector<axesName_t> m_axis;

    cluster(const std::vector< axesName_t> & ax) {
      for (auto & e : ax) {
        m_axis.push_back(e);
        m_buffer[e] = std::vector<double>();
      }
    }

    bool push( std::map<axesName_t, std::pair<double*, double> > & m_active_inputs) {
      for (const auto & e : m_axis) {
        if (!is_close(m_buffer[e], *(m_active_inputs[e].first), m_active_inputs[e].second)) {
          return false;
        }
      }
      for (const auto & e : m_axis) {
        m_buffer[e].push_back(*(m_active_inputs[e].first));
      }
      return true;
    }


    bool get_data(std::map<axesName_t, std::shared_ptr<double>>& p2, int cluster_ID) {
      double s = 0;
      for (auto& e : m_axis) {
        if (m_buffer[e].empty()) {
          return false;
        }
        double ava = 0;
        s = 0;
        for (const auto & d : m_buffer[e]) {
          ava += d;
          s += 1;
        }
        *p2[e] = ava/s;
      }
      *p2[axesName_t("ClusterSize")] = s;
      *p2[axesName_t("ClusterID")] = cluster_ID;
      return true;
    }
    void clear() {
      for (auto& e : m_buffer) {
        e.second.clear();
      }
    }
    
  };
  bool push_in_clusters(std::vector< cluster>& m_clusters, std::map<axesName_t, std::pair<double*, double> > & m_active_inputs) {
    for (auto& e : m_clusters) {
      if (e.push(m_active_inputs)) {
        return true;
      }
    }
    return false;
  }
  class processor_generic_cluster :public processor {
  public:
    processor_generic_cluster(const generic_plane& pl, const std::vector< std::pair<axesName_t, double> >& ax, const processor_prob& pprob);

    virtual init_returns init() override;

    virtual process_returns processEvent() override;

    virtual process_returns fill() override;

    virtual end_returns end() override;

    virtual processorName_t get_name() override;

    collection* get_output_collection();

    generic_plane m_plane1;

    std::shared_ptr<collection> m_output_coll;
    std::shared_ptr<generic_plane> m_outputPlane;
    processor_prob m_pprob;
    int m_current = 0;


    std::vector< cluster> m_clusters;
    std::map<axesName_t, std::shared_ptr<double>> m_p1;
    std::map<axesName_t, std::shared_ptr<double>> m_p2;

    std::map<axesName_t, std::pair<double*, double> > m_active_inputs;
    double* m_group_axis;
    double m_group_axis_last = 0;
    bool isEmpty = true;
  };

  processor_generic_cluster::processor_generic_cluster(const generic_plane& pl, const std::vector< std::pair<axesName_t, double> >& ax, const processor_prob& pprob) :m_plane1(pl), m_pprob(pprob)
  {
    std::vector<axesName_t> outNames;
    for (auto &e : pl.get_axes_names()) {
      outNames.push_back(e);
    }

    m_pprob.setProcessorCollection(pl.get_ProcessorCollection());
    m_pprob.setAxis(outNames);
    m_pprob.addAxis(axesName_t("ID"));
    m_pprob.addAxis(axesName_t("ClusterSize"));
    m_pprob.addAxis(axesName_t("ClusterID"));

    m_output_coll = Snew collection(m_pprob);
    m_outputPlane = Snew generic_plane(m_output_coll->getPlane(ID_t(0)));

    for (auto & e : m_plane1.get_axes_names()) {
      auto d = Snew double();
      m_plane1.setHitAxisAdress(e, d.get());
      m_p1[e] = d;
      auto d1 = Snew double();
      m_p2[e] = d1;
      m_outputPlane->setHitAxisAdress(e, d1.get());
    
      auto ax1 = std::find_if(ax.begin(), ax.end(), compare(e));
      if (ax1 != ax.end()) {
        m_active_inputs[e] = { d.get(), ax1->second };
      } else {
        m_active_inputs[e] = { d.get(), 1.0e30 };
      }
    }

    auto d1 = Snew double();
    m_p2[axesName_t("ClusterSize")] = d1;
    m_outputPlane->setHitAxisAdress(axesName_t("ClusterSize"), d1.get());

    auto d2 = Snew double();
    m_p2[axesName_t("ClusterID")] = d2;
    m_outputPlane->setHitAxisAdress(axesName_t("ClusterID"), d2.get());

  }


  init_returns processor_generic_cluster::init()
  {
    return i_sucess;
  }

  process_returns processor_generic_cluster::processEvent()
  {
    ++m_current;
    m_output_coll->clear_event();
    for (auto& e : m_clusters) {
      e.clear();
    }

    while (m_plane1.next()) {
      if (push_in_clusters(m_clusters, m_active_inputs)) {
        continue;
      }
      m_clusters.push_back(cluster(m_plane1.get_axes_names()));
      m_clusters.back().push(m_active_inputs);
    }

    return p_sucess;
  }

  process_returns processor_generic_cluster::fill()
  {
    int cluster_ID = 0;
    for (auto& c : m_clusters) {
      if (c.get_data(m_p2, cluster_ID++)) {
        m_outputPlane->push();
      }
    }
    m_output_coll->set_Event_Nr(m_current);
    m_output_coll->save();
    return p_sucess;
  }

  end_returns processor_generic_cluster::end()
  {
    return e_success;
  }

  processorName_t processor_generic_cluster::get_name()
  {
    return m_pprob.name;
  }

  collection* processor_generic_cluster::get_output_collection()
  {
    return m_output_coll.get();
  }

  generic_plane clustering(const generic_plane & pl, cl_conf conf, const processor_prob& pprob ) {
    
    std::vector< std::pair<axesName_t, double> > ax;
    for (int i = 0; i < conf.m_ax.size(); ++i) {
      ax.push_back({ conf.m_ax[i],conf.m_value[i] });
    }
    std::shared_ptr<processor> p(new processor_generic_cluster(pl, std::move(ax), pprob));
    pl.get_ProcessorCollection()->addProcessor(p);

    return dynamic_cast<processor_generic_cluster*>(p.get())->get_output_collection()->getPlane(ID_t(0));
  }
}