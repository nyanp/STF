#ifndef SPI_IFS_HPP_
#define SPI_IFS_HPP_

template<typename AC>
SPI<AC>::SSKeeper::SSKeeper(SPI<AC>& spi, unsigned int id) : spi_(spi)
{
	if(spi_.ss_locked_++){ return; }
	spi_.select_slave_(id);
}

template<typename AC>
SPI<AC>::SSKeeper::~SSKeeper()
{
	if(--spi_.ss_locked_){ return; }
	spi_.release_slave_();
}

template<typename AC>
bool SPI<AC>::is_mode_fault_error()
{
	AccessControl<AC> ac_obj;
	return SPISR_ & SPISR_MODF_ ? true : false;
}

template<typename AC>
bool SPI<AC>::is_tx_fifo_full()
{
	AccessControl<AC> ac_obj;
	return SPISR_ & SPISR_Tx_FULL_ ? true : false;
}

template<typename AC>
bool SPI<AC>::is_tx_fifo_empty()
{
	AccessControl<AC> ac_obj;
	return SPISR_ & SPISR_Tx_EMPTY_ ? true : false;
}

template<typename AC>
bool SPI<AC>::is_rx_fifo_full()
{
	AccessControl<AC> ac_obj;
	return SPISR_ & SPISR_Rx_FULL_ ? true : false;
}

template<typename AC>
bool SPI<AC>::is_rx_fifo_empty()
{
	AccessControl<AC> ac_obj;
	return SPISR_ & SPISR_Rx_EMPTY_ ? true : false;
}

template<typename AC>
void SPI<AC>::reset()
{
	AccessControl<AC> ac_obj;
	SRR_ = SRR_VALUE_;
}

template<typename AC>
void SPI<AC>::reset_tx_fifo()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_Tx_FIFO_RESET_;
}

template<typename AC>
void SPI<AC>::reset_rx_fifo()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_Rx_FIFO_RESET_;
}

template<typename AC>
void SPI<AC>::enable_spi_()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_SPE_;
}

template<typename AC>
void SPI<AC>::disable_spi_()
{
	AccessControl<AC> ac_obj;
	SPICR_ &= ~SPICR_SPE_;
}

template<typename AC>
void SPI<AC>::enable_master_mode_()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_MASTER_;
}

template<typename AC>
void SPI<AC>::enable_slave_mode_()
{
	AccessControl<AC> ac_obj;
	SPICR_ &= ~SPICR_MASTER_;
}

template<typename AC>
void SPI<AC>::enable_manual_slave_select_assertion_()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_MANUAL_SLAVE_SELECT_ASSERTION_ENABLE_;
}

template<typename AC>
void SPI<AC>::disable_manual_slave_select_assertion_()
{
	AccessControl<AC> ac_obj;
	SPICR_ &= ~SPICR_MANUAL_SLAVE_SELECT_ASSERTION_ENABLE_;
}

template<typename AC>
void SPI<AC>::enable_clock_phase_first_()
{
	AccessControl<AC> ac_obj;
	SPICR_ &= ~SPICR_CPHA_;
}

template<typename AC>
void SPI<AC>::enable_clock_phase_second_()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_CPHA_;
}

template<typename AC>
void SPI<AC>::enable_active_low_()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_CPOL_;
}

template<typename AC>
void SPI<AC>::enable_active_high_()
{
	AccessControl<AC> ac_obj;
	SPICR_ &= ~SPICR_CPOL_;
}

template<typename AC>
void SPI<AC>::enable_master_transaction_()
{
	AccessControl<AC> ac_obj;
	SPICR_ &= ~SPICR_MASTER_TRANSACTION_INHIBIT_;
}

template<typename AC>
void SPI<AC>::disable_master_transaction_()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_MASTER_TRANSACTION_INHIBIT_;
}

template<typename AC>
void SPI<AC>::enable_lsb_first_()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_LSB_FIRST_;
}

template<typename AC>
void SPI<AC>::enable_msb_first_()
{
	AccessControl<AC> ac_obj;
	SPICR_ &= ~SPICR_LSB_FIRST_;
}

template<typename AC>
void SPI<AC>::enable_loopback_()
{
	AccessControl<AC> ac_obj;
	SPICR_ |= SPICR_LOOP_;
} 

template<typename AC>
void SPI<AC>::disable_loopback_()
{
	AccessControl<AC> ac_obj;
	SPICR_ &= ~SPICR_LOOP_;
}

template<typename AC>
void SPI<AC>::select_slave_(unsigned int id)
{
	AccessControl<AC> ac_obj;
	SPISSR_ = ~(1<<id);
}

template<typename AC>
void SPI<AC>::release_slave_()
{
	AccessControl<AC> ac_obj;
	SPISSR_ = 0xffffffff;
}

#endif /*SPI_IFS_HPP_*/
