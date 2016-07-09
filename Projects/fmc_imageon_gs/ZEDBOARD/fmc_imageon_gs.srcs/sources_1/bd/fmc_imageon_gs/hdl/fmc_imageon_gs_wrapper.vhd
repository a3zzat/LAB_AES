--Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2015.4 (win64) Build 1412921 Wed Nov 18 09:43:45 MST 2015
--Date        : Tue Jul 05 13:22:07 2016
--Host        : MyIdeaPad running 64-bit major release  (build 9200)
--Command     : generate_target fmc_imageon_gs_wrapper.bd
--Design      : fmc_imageon_gs_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity fmc_imageon_gs_wrapper is
  port (
    ADDRESS : out STD_LOGIC_VECTOR ( 1 downto 0 );
    BCLK : out STD_LOGIC;
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FCLK_CLK3 : out STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    IO_HDMII_clk : in STD_LOGIC;
    IO_HDMII_data : in STD_LOGIC_VECTOR ( 15 downto 0 );
    IO_HDMII_spdif : in STD_LOGIC;
    IO_HDMIO_clk : out STD_LOGIC;
    IO_HDMIO_data : out STD_LOGIC_VECTOR ( 15 downto 0 );
    IO_HDMIO_spdif : out STD_LOGIC;
    IO_VITA_CAM_clk_out_n : in STD_LOGIC;
    IO_VITA_CAM_clk_out_p : in STD_LOGIC;
    IO_VITA_CAM_clk_pll : out STD_LOGIC;
    IO_VITA_CAM_data_n : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IO_VITA_CAM_data_p : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IO_VITA_CAM_monitor : in STD_LOGIC_VECTOR ( 1 downto 0 );
    IO_VITA_CAM_reset_n : out STD_LOGIC;
    IO_VITA_CAM_sync_n : in STD_LOGIC;
    IO_VITA_CAM_sync_p : in STD_LOGIC;
    IO_VITA_CAM_trigger : out STD_LOGIC_VECTOR ( 2 downto 0 );
    IO_VITA_SPI_spi_miso : in STD_LOGIC;
    IO_VITA_SPI_spi_mosi : out STD_LOGIC;
    IO_VITA_SPI_spi_sclk : out STD_LOGIC;
    IO_VITA_SPI_spi_ssel_n : out STD_LOGIC;
    LRCLK : out STD_LOGIC;
    SDATA_I : in STD_LOGIC;
    SDATA_O : out STD_LOGIC;
    fmc_imageon_iic_rst_n : out STD_LOGIC_VECTOR ( 0 to 0 );
    fmc_imageon_iic_scl_io : inout STD_LOGIC;
    fmc_imageon_iic_sda_io : inout STD_LOGIC;
    fmc_imageon_vclk : in STD_LOGIC;
    iic_1_scl_io : inout STD_LOGIC;
    iic_1_sda_io : inout STD_LOGIC
  );
end fmc_imageon_gs_wrapper;

architecture STRUCTURE of fmc_imageon_gs_wrapper is
  component fmc_imageon_gs is
  port (
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    IO_HDMII_data : in STD_LOGIC_VECTOR ( 15 downto 0 );
    IO_HDMII_spdif : in STD_LOGIC;
    IO_HDMIO_clk : out STD_LOGIC;
    IO_HDMIO_data : out STD_LOGIC_VECTOR ( 15 downto 0 );
    IO_HDMIO_spdif : out STD_LOGIC;
    IO_VITA_CAM_data_p : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IO_VITA_CAM_sync_p : in STD_LOGIC;
    IO_VITA_CAM_sync_n : in STD_LOGIC;
    IO_VITA_CAM_reset_n : out STD_LOGIC;
    IO_VITA_CAM_trigger : out STD_LOGIC_VECTOR ( 2 downto 0 );
    IO_VITA_CAM_monitor : in STD_LOGIC_VECTOR ( 1 downto 0 );
    IO_VITA_CAM_clk_pll : out STD_LOGIC;
    IO_VITA_CAM_data_n : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IO_VITA_CAM_clk_out_p : in STD_LOGIC;
    IO_VITA_CAM_clk_out_n : in STD_LOGIC;
    IO_VITA_SPI_spi_sclk : out STD_LOGIC;
    IO_VITA_SPI_spi_ssel_n : out STD_LOGIC;
    IO_VITA_SPI_spi_mosi : out STD_LOGIC;
    IO_VITA_SPI_spi_miso : in STD_LOGIC;
    fmc_imageon_iic_scl_i : in STD_LOGIC;
    fmc_imageon_iic_scl_o : out STD_LOGIC;
    fmc_imageon_iic_scl_t : out STD_LOGIC;
    fmc_imageon_iic_sda_i : in STD_LOGIC;
    fmc_imageon_iic_sda_o : out STD_LOGIC;
    fmc_imageon_iic_sda_t : out STD_LOGIC;
    IIC_1_sda_i : in STD_LOGIC;
    IIC_1_sda_o : out STD_LOGIC;
    IIC_1_sda_t : out STD_LOGIC;
    IIC_1_scl_i : in STD_LOGIC;
    IIC_1_scl_o : out STD_LOGIC;
    IIC_1_scl_t : out STD_LOGIC;
    IO_HDMII_clk : in STD_LOGIC;
    fmc_imageon_vclk : in STD_LOGIC;
    fmc_imageon_iic_rst_n : out STD_LOGIC_VECTOR ( 0 to 0 );
    FCLK_CLK3 : out STD_LOGIC;
    SDATA_I : in STD_LOGIC;
    BCLK : out STD_LOGIC;
    LRCLK : out STD_LOGIC;
    SDATA_O : out STD_LOGIC;
    ADDRESS : out STD_LOGIC_VECTOR ( 1 downto 0 )
  );
  end component fmc_imageon_gs;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal fmc_imageon_iic_scl_i : STD_LOGIC;
  signal fmc_imageon_iic_scl_o : STD_LOGIC;
  signal fmc_imageon_iic_scl_t : STD_LOGIC;
  signal fmc_imageon_iic_sda_i : STD_LOGIC;
  signal fmc_imageon_iic_sda_o : STD_LOGIC;
  signal fmc_imageon_iic_sda_t : STD_LOGIC;
  signal iic_1_scl_i : STD_LOGIC;
  signal iic_1_scl_o : STD_LOGIC;
  signal iic_1_scl_t : STD_LOGIC;
  signal iic_1_sda_i : STD_LOGIC;
  signal iic_1_sda_o : STD_LOGIC;
  signal iic_1_sda_t : STD_LOGIC;
begin
fmc_imageon_gs_i: component fmc_imageon_gs
     port map (
      ADDRESS(1 downto 0) => ADDRESS(1 downto 0),
      BCLK => BCLK,
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
      DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
      DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
      DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FCLK_CLK3 => FCLK_CLK3,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      IIC_1_scl_i => iic_1_scl_i,
      IIC_1_scl_o => iic_1_scl_o,
      IIC_1_scl_t => iic_1_scl_t,
      IIC_1_sda_i => iic_1_sda_i,
      IIC_1_sda_o => iic_1_sda_o,
      IIC_1_sda_t => iic_1_sda_t,
      IO_HDMII_clk => IO_HDMII_clk,
      IO_HDMII_data(15 downto 0) => IO_HDMII_data(15 downto 0),
      IO_HDMII_spdif => IO_HDMII_spdif,
      IO_HDMIO_clk => IO_HDMIO_clk,
      IO_HDMIO_data(15 downto 0) => IO_HDMIO_data(15 downto 0),
      IO_HDMIO_spdif => IO_HDMIO_spdif,
      IO_VITA_CAM_clk_out_n => IO_VITA_CAM_clk_out_n,
      IO_VITA_CAM_clk_out_p => IO_VITA_CAM_clk_out_p,
      IO_VITA_CAM_clk_pll => IO_VITA_CAM_clk_pll,
      IO_VITA_CAM_data_n(3 downto 0) => IO_VITA_CAM_data_n(3 downto 0),
      IO_VITA_CAM_data_p(3 downto 0) => IO_VITA_CAM_data_p(3 downto 0),
      IO_VITA_CAM_monitor(1 downto 0) => IO_VITA_CAM_monitor(1 downto 0),
      IO_VITA_CAM_reset_n => IO_VITA_CAM_reset_n,
      IO_VITA_CAM_sync_n => IO_VITA_CAM_sync_n,
      IO_VITA_CAM_sync_p => IO_VITA_CAM_sync_p,
      IO_VITA_CAM_trigger(2 downto 0) => IO_VITA_CAM_trigger(2 downto 0),
      IO_VITA_SPI_spi_miso => IO_VITA_SPI_spi_miso,
      IO_VITA_SPI_spi_mosi => IO_VITA_SPI_spi_mosi,
      IO_VITA_SPI_spi_sclk => IO_VITA_SPI_spi_sclk,
      IO_VITA_SPI_spi_ssel_n => IO_VITA_SPI_spi_ssel_n,
      LRCLK => LRCLK,
      SDATA_I => SDATA_I,
      SDATA_O => SDATA_O,
      fmc_imageon_iic_rst_n(0) => fmc_imageon_iic_rst_n(0),
      fmc_imageon_iic_scl_i => fmc_imageon_iic_scl_i,
      fmc_imageon_iic_scl_o => fmc_imageon_iic_scl_o,
      fmc_imageon_iic_scl_t => fmc_imageon_iic_scl_t,
      fmc_imageon_iic_sda_i => fmc_imageon_iic_sda_i,
      fmc_imageon_iic_sda_o => fmc_imageon_iic_sda_o,
      fmc_imageon_iic_sda_t => fmc_imageon_iic_sda_t,
      fmc_imageon_vclk => fmc_imageon_vclk
    );
fmc_imageon_iic_scl_iobuf: component IOBUF
     port map (
      I => fmc_imageon_iic_scl_o,
      IO => fmc_imageon_iic_scl_io,
      O => fmc_imageon_iic_scl_i,
      T => fmc_imageon_iic_scl_t
    );
fmc_imageon_iic_sda_iobuf: component IOBUF
     port map (
      I => fmc_imageon_iic_sda_o,
      IO => fmc_imageon_iic_sda_io,
      O => fmc_imageon_iic_sda_i,
      T => fmc_imageon_iic_sda_t
    );
iic_1_scl_iobuf: component IOBUF
     port map (
      I => iic_1_scl_o,
      IO => iic_1_scl_io,
      O => iic_1_scl_i,
      T => iic_1_scl_t
    );
iic_1_sda_iobuf: component IOBUF
     port map (
      I => iic_1_sda_o,
      IO => iic_1_sda_io,
      O => iic_1_sda_i,
      T => iic_1_sda_t
    );
end STRUCTURE;
