
    
    struct analysis_config 
    {
        double TriggerASIC,
        TriggerChannel,
        LookbackStart,
        LookbackStop,
        LookbackStart_fine,
        LookbackStop_fine,
        TS_offset,
        TS_slope,
        TS_Cut;
    };


typedef std::map<double, analysis_config> run_config_t;
typedef std::map<int, run_config_t> config_t;


config_t config() {
    config_t ret; {
        analysis_config d1;
        d1.LookbackStart = 100;
        d1.LookbackStop = 150;
        d1.LookbackStart_fine = 119;
        d1.LookbackStop_fine = 121;
        d1.TriggerASIC = 7;
        d1.TriggerChannel = 15;
        ret[227][2] = d1;
    } {
        analysis_config d1;
        d1.LookbackStart = 100;
        d1.LookbackStop = 150;
        d1.LookbackStart_fine = 119;
        d1.LookbackStop_fine = 121;
        d1.TriggerASIC = 8;
        d1.TriggerChannel = 14;
        ret[227][12] = d1;
    } 

    return ret;
}
