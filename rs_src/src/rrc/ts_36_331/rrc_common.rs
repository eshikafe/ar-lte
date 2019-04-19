// PDCP-Config information element 

enum DiscardTimer {
    ms50 = 50,
    ms100 = 100,
    ms150 = 150,
    ms300 = 300,
    ms500 = 500,
    ms750 = 750,
    ms1500 = 1500,
    infinity = 0,
}

struct RrcPdcpConfig {
    discard_timer: DiscardTimer,
}