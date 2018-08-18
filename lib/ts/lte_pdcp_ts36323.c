#include "lte_pdcp_ts36323.h"


 struct pdcp_Entity {
    def __init__(self, pdcp_pdu data, Timer timer):
        # Separate the SDU data from the PDU
        self.pdcp_sdu = data.pdcp_sdu
        data.pdcp_sdu = NULL
        self.pdcp_pdu = data

        # 7.1 Variables
        # PDCP SN of the next PDCP SDU for a given PDCP entity
        cdef unsigned int self.next_pdcp_tx_sn = 0

        # HFN value for the generation of the COUNT value
        #  used for PDCP PDUs for a given PDCP entity
        cdef unsigned int self.tx_hfn = 0

        # The next expected PDCP SN by the receiver for a given PDCP entity
        cdef unsigned int self.next_pdcp_rx_sfn = 0

        cdef unsigned int self.rx_hfn = 0

        # Last_Submitted_PDCP_RX_SN indicates the SN of the last PDCP SDU delivered to the upper layers.
        cdef unsigned int self.last_submitted_pdcp_rx_sfn = MAXIMUM_PDCP_SN[self.pdcp_pdu.sfn_type]

        # This variable is used only when the reordering function is used.
        # This variable holds the value of the COUNT following
        #  the COUNT value associated with the PDCP PDU which triggered t-Reordering
        cdef uint self.reordering_pdcp_rx_count

        # 7.2 Timers
        # The duration of the timer is configured by upper layers.
        # In the transmitter, a new timer is started upon reception of an SDU from upper layer. 
        cdef uint self.discardTimer = timer.discardTimer

        # This timer is used to detect loss of PDCP PDUs as specified
        # in the subclause 5.1.2.1.4. If t-Reordering is running,
        # t-Reordering shall not be started additionally, i.e. only one tReordering
        # per PDCP entity is running at a given time. 
        cdef uint self.tReordering = timer.tReordering

}
// Transmitting (i.e Downlink)
  
void sequence_numbering(self) {

}


/* RoHC compressor */
void header_compression(struct pdcp_pdu *pp) {
        /* User plane only */
        if (pp->plane == PDCP_USER_PLANE) && (pp->plane.direction == PDCP_TX)
        {
            if (pp->pdps.sdu_type == SDU_TYPE_IP)
                rohc_compressor(pp->pdcp_sdu);
        }
}

void integrity_protection(struct pdcp_pdu *pp) 
{
        /* Control plane only */

}

void ciphering(struct pdcp_pdu *pp)
{
        // TODO
}

void add_pdcp_header(struct pdcp_pdu *pp)
{
        // TODO
}

void routing(struct pdcp_pdu *pp)
{
        // TODO
}

    # -----------------------
    # Receiving (i.e Uplink)
    # -----------------------
    def remove_pdcp_header(self, pdcp_data):
        # TODO
        
    def deciphering(self, pdcp_data):
        # TODO

    def integrity_verification(self, pdcp_data):
        # Inputs: COUNT and direction (TS 36.323 5.7)
        # Control plane only
        # TODO

    def reordering(self, pdcp_data):
        # User plane only
        # TODO

    # RoHC decompressor
    def header_decompression(self, pdcp_data):
        # User plane only
        rohc.decompressor(pdcp_data)

    def in_order_delivery_duplicate_detection(self, pdcp_data):
        # User plane only
        # TODO

    
    
