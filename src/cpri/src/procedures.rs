use std::net::UdpSocket;

mod types;
use types::*;

impl EventIndicationMessage {
    pub fn new() -> EventIndicationMessage {
        EventIndicationMessage {
            event_id: 0u8,
            event_type: EventType::NotificationIndication,
            seq_num: 0u8,
            num_faults_notif: 0u8,
            alarm: Vec::new(),
        }
    }
    pub fn set_event_id(&mut self, event_id: u8) {
        self.event_id = event_id;
    }

    pub fn incr_seq_num(&mut self) {
        self.seq_num += 1;
    }

    pub fn set_event_type(&mut self, event_type: EventType) {
        self.event_type = event_type;
    }

    pub fn send(&mut self, event_type: EventType) -> Result<(), String> {
        match event_type {
            EventType::FaultsIndications => {
                self.event_id = self.set_event_id(100u8);
                self.event_type = EventType::FaultsIndications;
                self.seq_num = self.incr_seq_num();
                self.num_faults_notif = 2;
                //assert_ne!(self.num_faults_notif, 0);
                                
            }
        }
    }
}
