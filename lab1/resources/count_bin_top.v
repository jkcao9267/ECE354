module count_bin_top 

	(
		// Clock pins
		CLOCK_50,
		
		
		// SDRAM
		DRAM_ADDR,
		DRAM_BA,
		DRAM_CAS_N,
		DRAM_CKE,
		DRAM_CLK,
		DRAM_CS_N,
		DRAM_DQ,
		DRAM_LDQM,
		DRAM_RAS_N,
		DRAM_UDQM,
		DRAM_WE_N,
		
		
		// Seven Segment Displays
		HEX4,
		HEX5,
		
		// LEDs
		
		LEDR,
		
		// Slider Switches
		SW
		
		
	);
		
	// Clock pins	
	input CLOCK_50;
	
	// SDRAM
	output 		[12: 0]	DRAM_ADDR;
	output		[ 1: 0]	DRAM_BA;
	output					DRAM_CAS_N;
	output					DRAM_CKE;
	output					DRAM_CLK;
	output					DRAM_CS_N;
	inout			[15: 0]	DRAM_DQ;
	output					DRAM_LDQM;
	output					DRAM_RAS_N;
	output					DRAM_UDQM;
	output					DRAM_WE_N;
	
	// Seven Segment Displays
	output		[ 6: 0]	HEX4;
	output		[ 6: 0]	HEX5;
	
	// LEDs
	output		[ 7: 0]	LEDR;
	
	// Slider Switches
	input			[ 3: 0]	SW;
	
	
	wire [15:0] hex5_hex4;

	assign HEX4 = ~hex5_hex4[ 6: 0];
	assign HEX5 = ~hex5_hex4[ 14: 8];
	
	
count_bin bin_count (
	
	
		.sdram_pll_ref_clk_clk  (CLOCK_50),
		.sdram_pll_ref_reset_reset (1'b0),
		
		.switch_export_export (SW),
		
		.leds_export_export (LEDR),
		
		.hex_export_export (hex5_hex4),
		
		 // SDRAM
		.sdram_clk_clk								(DRAM_CLK),
		.sdram_addr									(DRAM_ADDR),
		.sdram_ba									(DRAM_BA),
		.sdram_cas_n								(DRAM_CAS_N),
		.sdram_cke									(DRAM_CKE),
		.sdram_cs_n									(DRAM_CS_N),
		.sdram_dq									(DRAM_DQ),
		.sdram_dqm									({DRAM_UDQM,DRAM_LDQM}),
		.sdram_ras_n								(DRAM_RAS_N),
		.sdram_we_n									(DRAM_WE_N),
			
		);
		
		
		endmodule
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	