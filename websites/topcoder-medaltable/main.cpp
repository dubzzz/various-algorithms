#include "gtest/gtest.h"

#include <string>
#include <utility>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto data = std::vector<std::string>{"ITA JPN AUS", "KOR TPE UKR", "KOR KOR GBR", "KOR CHN TPE"};
  auto expected = std::vector<std::string>{"KOR 3 1 0", "ITA 1 0 0", "TPE 0 1 1", "CHN 0 1 0", "JPN 0 1 0", "AUS 0 0 1", "GBR 0 0 1", "UKR 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Example1)
{
  auto data = std::vector<std::string>{"USA AUT ROM"};
  auto expected = std::vector<std::string>{"USA 1 0 0",  "AUT 0 1 0",  "ROM 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Example2)
{
  auto data = std::vector<std::string>{"GER AUT SUI", "AUT SUI GER", "SUI GER AUT"};
  auto expected = std::vector<std::string>{"AUT 1 1 1",  "GER 1 1 1",  "SUI 1 1 1"};
  ASSERT_EQ(expected, medal_table(data));
}

TEST(TEST_NAME, Extended0)
{
  auto data = std::vector<std::string>{"SOL MOZ BOT", "JOR CUB GUA", "TPE MRI BLR", "KEN NRU KSA", "PAK BLR TPE", "MLT CZE BRA", "KAZ TLS NCA", "TLS ECU GBS", "NRU ECU TAN", "ANG PAR CAF", "KGZ KUW PLE", "NRU AZE ANT", "BEL YUG NCA", "CHA KGZ GRE", "PUR CUB KGZ", "PAK THA PUR", "TLS GUA NRU", "KUW GBS ANT", "UGA ARG GBS", "SRI ARG BOT", "ANT MOZ PAK", "SOL EST PUR", "THA GRN RSA", "MLT MRI GBS", "UGA GUY MRI", "KEN CGO KSA", "GBS BOT UGA", "AZE PAK EST", "BOT NGR GRN", "KAZ KUW GUY", "NCA MLT AZE"};
  auto expected = std::vector<std::string>{"NRU 2 1 1", "PAK 2 1 1", "MLT 2 1 0", "TLS 2 1 0", "UGA 2 0 1", "KAZ 2 0 0", "KEN 2 0 0", "SOL 2 0 0", "KUW 1 2 0", "GBS 1 1 3", "BOT 1 1 2", "AZE 1 1 1", "KGZ 1 1 1", "THA 1 1 0", "ANT 1 0 2", "NCA 1 0 2", "PUR 1 0 2", "TPE 1 0 1", "ANG 1 0 0", "BEL 1 0 0", "CHA 1 0 0", "JOR 1 0 0", "SRI 1 0 0", "MRI 0 2 1", "ARG 0 2 0", "CUB 0 2 0", "ECU 0 2 0", "MOZ 0 2 0", "BLR 0 1 1", "EST 0 1 1", "GRN 0 1 1", "GUA 0 1 1", "GUY 0 1 1", "CGO 0 1 0", "CZE 0 1 0", "NGR 0 1 0", "PAR 0 1 0", "YUG 0 1 0", "KSA 0 0 2", "BRA 0 0 1", "CAF 0 0 1", "GRE 0 0 1", "PLE 0 0 1", "RSA 0 0 1", "TAN 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended1)
{
  auto data = std::vector<std::string>{"KEN JAM BAN", "SEN DEN DEN", "PAN BLR RSA", "BAN FRG KAZ", "PAN GAB FIJ", "FIJ TRI ISL", "SEN GAM MAD", "RSA ZIM HON", "ISV SMR RSA", "BAR PER BAN", "NED GAB LES", "SCG DMA UAE", "BRN BAR BAN", "VEN CHN HON", "KAZ ZIM SEN", "TRI FRG RSA", "HON CHN CHI", "BAR AHO CHN", "KSA KAZ BAR", "GAM NED SMR", "JAM HON ERI", "BUL EUN LES", "BUL ISL NZL", "CUB ISL AFG", "NED ARG ZIM", "KEN AFG FRG", "GEO HUN LCA", "LCA KSA MAD", "SMR CHI DEN", "ZIM LCA ZIM", "TRI BUR HUN", "DEN FRG RSA"};
  auto expected = std::vector<std::string>{"BAR 2 1 1", "NED 2 1 0", "TRI 2 1 0", "SEN 2 0 1", "BUL 2 0 0", "KEN 2 0 0", "PAN 2 0 0", "ZIM 1 2 2", "DEN 1 1 2", "HON 1 1 2", "KAZ 1 1 1", "LCA 1 1 1", "SMR 1 1 1", "GAM 1 1 0", "JAM 1 1 0", "KSA 1 1 0", "RSA 1 0 4", "BAN 1 0 3", "FIJ 1 0 1", "BRN 1 0 0", "CUB 1 0 0", "GEO 1 0 0", "ISV 1 0 0", "SCG 1 0 0", "VEN 1 0 0", "FRG 0 3 1", "CHN 0 2 1", "ISL 0 2 1", "GAB 0 2 0", "AFG 0 1 1", "CHI 0 1 1", "HUN 0 1 1", "AHO 0 1 0", "ARG 0 1 0", "BLR 0 1 0", "BUR 0 1 0", "DMA 0 1 0", "EUN 0 1 0", "PER 0 1 0", "LES 0 0 2", "MAD 0 0 2", "ERI 0 0 1", "NZL 0 0 1", "UAE 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended2)
{
  auto data = std::vector<std::string>{"ITA NGR INA", "ZAM RWA SOM", "YUG CYP YUG", "RWA IRQ RWA", "BER MOZ GDR", "NRU MYA BAR", "SWZ BAH MEX", "GDR IRI IVB", "AHO BAR BIZ", "SOM MEX NED", "SRI BAR HUN", "GAM BAH CYP", "BUL BAH IVB", "BER SWZ ANG", "ANG BDI NED", "HUN SOM GBR", "MAD ROM INA", "BEN BEN YUG", "NRU BEN ARU", "YUG ARU NAM", "NAM YUG RWA", "BAH GAM TRI", "GBR MEX AHO", "TRI PAK UAE", "ZAM RWA ARU", "NAM CYP UAE", "ARU SOM NRU", "ITA ANG TRI", "ITA PAK BEL", "MEX NRU BIZ", "CZE HUN BIZ", "BAH MAD JAM", "AHO YUG BDI"};
  auto expected = std::vector<std::string>{"ITA 3 0 0", "BAH 2 3 0", "YUG 2 2 2", "NRU 2 1 1", "AHO 2 0 1", "NAM 2 0 1", "BER 2 0 0", "ZAM 2 0 0", "RWA 1 2 2", "MEX 1 2 1", "SOM 1 2 1", "BEN 1 2 0", "ARU 1 1 2", "ANG 1 1 1", "HUN 1 1 1", "GAM 1 1 0", "MAD 1 1 0", "SWZ 1 1 0", "TRI 1 0 2", "GBR 1 0 1", "GDR 1 0 1", "BUL 1 0 0", "CZE 1 0 0", "SRI 1 0 0", "BAR 0 2 1", "CYP 0 2 1", "PAK 0 2 0", "BDI 0 1 1", "IRI 0 1 0", "IRQ 0 1 0", "MOZ 0 1 0", "MYA 0 1 0", "NGR 0 1 0", "ROM 0 1 0", "BIZ 0 0 3", "INA 0 0 2", "IVB 0 0 2", "NED 0 0 2", "UAE 0 0 2", "BEL 0 0 1", "JAM 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended3)
{
  auto data = std::vector<std::string>{"VAN GRE MDA", "PLW SKN MAD", "LTU CIV GBR", "GUY CAY COL", "ESP POR ARM", "VAN MAD URS", "GER BOL MOZ", "NAM VAN SKN", "VEN KSA ARU", "NED NRU TUR", "CIV MDA ESP", "POR GBR CAY", "ESP SKN ESP", "NAM DJI HUN", "RSA LTU CAY", "SUI KSA PER", "QAT ROM ROM", "GER KSA PLW", "CGO GRE CGO", "DJI ZIM QAT", "CAY CRC GRE", "GUY URU PER", "LIE COL LIE", "QAT RSA PER", "CIV MOZ CIV", "GBR LAT NAM", "ARM CRC GUY", "ROM LUX ROM", "LTU PER CIV", "NRU TUR COL", "KSA ZIM GRE", "RSA HUN EST", "LBA URS LIE", "VEN NRU ESP"};
  auto expected = std::vector<std::string>{"CIV 2 1 2", "LTU 2 1 0", "RSA 2 1 0", "VAN 2 1 0", "ESP 2 0 3", "GUY 2 0 1", "NAM 2 0 1", "QAT 2 0 1", "GER 2 0 0", "VEN 2 0 0", "KSA 1 3 0", "NRU 1 2 0", "CAY 1 1 2", "ROM 1 1 2", "GBR 1 1 1", "DJI 1 1 0", "POR 1 1 0", "LIE 1 0 2", "ARM 1 0 1", "CGO 1 0 1", "PLW 1 0 1", "LBA 1 0 0", "NED 1 0 0", "SUI 1 0 0", "GRE 0 2 2", "SKN 0 2 1", "CRC 0 2 0", "ZIM 0 2 0", "PER 0 1 3", "COL 0 1 2", "HUN 0 1 1", "MAD 0 1 1", "MDA 0 1 1", "MOZ 0 1 1", "TUR 0 1 1", "URS 0 1 1", "BOL 0 1 0", "LAT 0 1 0", "LUX 0 1 0", "URU 0 1 0", "ARU 0 0 1", "EST 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended4)
{
  auto data = std::vector<std::string>{"BER POR THA", "MAD BER GAM", "SUD GRN TLS", "GRN BER OMA", "ISL OMA GHA", "NRU TLS LAO", "MDA TLS PUR", "ARU TLS LAO", "GAM FIJ NAM", "MEX ETH MAD", "SCG GUI DEN", "OMA TRI GHA", "UGA PRK RWA", "THA ARU TLS", "IVB MLT MAD", "THA DEN GRN", "GHA PUR FIJ", "BER SYR CHA", "NRU AZE IRI", "DJI PAR PRK", "SUD IVB AZE", "ANT BER AFG", "GRN ARU PRK", "CAF TUN SUD", "ZIM GUY GHA", "MDA FIJ MEX", "UGA NZL GEQ", "DEN PUR BER", "GUY GRN DJI", "TKM OMA UGA", "NAM IRI GUY", "POR ISL MEX", "POR SYR PAR", "ISL YEM NRU", "FIJ VIE AFG"};
  auto expected = std::vector<std::string>{"BER 2 3 1", "GRN 2 2 1", "ISL 2 1 0", "POR 2 1 0", "NRU 2 0 1", "SUD 2 0 1", "THA 2 0 1", "UGA 2 0 1", "MDA 2 0 0", "FIJ 1 2 1", "OMA 1 2 1", "ARU 1 2 0", "DEN 1 1 1", "GUY 1 1 1", "IVB 1 1 0", "GHA 1 0 3", "MAD 1 0 2", "MEX 1 0 2", "DJI 1 0 1", "GAM 1 0 1", "NAM 1 0 1", "ANT 1 0 0", "CAF 1 0 0", "SCG 1 0 0", "TKM 1 0 0", "ZIM 1 0 0", "TLS 0 3 2", "PUR 0 2 1", "SYR 0 2 0", "PRK 0 1 2", "AZE 0 1 1", "IRI 0 1 1", "PAR 0 1 1", "ETH 0 1 0", "GUI 0 1 0", "MLT 0 1 0", "NZL 0 1 0", "TRI 0 1 0", "TUN 0 1 0", "VIE 0 1 0", "YEM 0 1 0", "AFG 0 0 2", "LAO 0 0 2", "CHA 0 0 1", "GEQ 0 0 1", "RWA 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended5)
{
  auto data = std::vector<std::string>{"MGL VIE GAB", "CAN KSA SVK", "EGY CUB ESP", "GEO MAR EGY", "SVK BIH OMA", "EGY CAY RUS", "FSM SUR SVK", "MGL GHA VEN", "LCA SUI RUS", "SCG LBA RUS", "MAW BIH PER", "THA CIV BIH", "RUS FIN CZE", "URS RUS RUS", "CAY JOR SIN", "SCG RUS SUI", "GAB UZB MAW", "CIV LBA TRI", "CAF VEN SCG", "SKN RUS CUB", "GAB CZE DJI", "URU YUG FIJ", "VEN SIN MGL", "CIV MLI EGY", "SUI SCG SCG", "KSA GEO FIN", "ESP SCG EUN", "SLE SMR SLE", "ROM THA SIN", "FSM MGL GEO", "JOR TRI MAW", "OMA SVK MAW", "THA SMR ESP", "HAI UGA SUI", "OMA SCG KSA", "ESP COK SUR"};
  auto expected = std::vector<std::string>{"SCG 2 3 2", "MGL 2 1 1", "CIV 2 1 0", "THA 2 1 0", "EGY 2 0 2", "ESP 2 0 2", "GAB 2 0 1", "OMA 2 0 1", "FSM 2 0 0", "RUS 1 3 4", "SUI 1 1 2", "SVK 1 1 2", "GEO 1 1 1", "KSA 1 1 1", "VEN 1 1 1", "CAY 1 1 0", "JOR 1 1 0", "MAW 1 0 3", "SLE 1 0 1", "CAF 1 0 0", "CAN 1 0 0", "HAI 1 0 0", "LCA 1 0 0", "ROM 1 0 0", "SKN 1 0 0", "URS 1 0 0", "URU 1 0 0", "BIH 0 2 1", "LBA 0 2 0", "SMR 0 2 0", "SIN 0 1 2", "CUB 0 1 1", "CZE 0 1 1", "FIN 0 1 1", "SUR 0 1 1", "TRI 0 1 1", "COK 0 1 0", "GHA 0 1 0", "MAR 0 1 0", "MLI 0 1 0", "UGA 0 1 0", "UZB 0 1 0", "VIE 0 1 0", "YUG 0 1 0", "DJI 0 0 1", "EUN 0 0 1", "FIJ 0 0 1", "PER 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended6)
{
  auto data = std::vector<std::string>{"NOR ESA LIB", "NAM HUN SVK", "PER RSA PER", "HUN CZE PLE", "CGO BIH DMA", "ESA INA SOL", "GDR ARM ANG", "ESA NAM YEM", "GRE BIH IRL", "FSM CAY ARG", "ETH SAM EST", "SOL INA POL", "POL CZE LUX", "HUN MON POL", "CAY SAM SOL", "HON ARM FSM", "DMA HKG GRE", "DMA NOR ARG", "ESA ANG CAY", "ROM GRE ETH", "RSA NAM BIH", "BIH LAT MEX", "SOL ESA ROM", "HKG PLW HON", "CAY TAN DEN", "YEM ETH FSM", "ETH LBA PLW", "NOR RSA HKG", "PLE ARM HUN", "SVK SAM RSA", "CZE MYA IRL", "ETH PLE VIE", "THA LIB EST", "NOR VIE YEM", "BOL BOL SVK", "GUI CAY DEN", "NOR IRL PLW"};
  auto expected = std::vector<std::string>{"NOR 4 1 0", "ESA 3 2 0", "ETH 3 1 1", "CAY 2 2 1", "HUN 2 1 1", "SOL 2 0 2", "DMA 2 0 1", "BIH 1 2 1", "RSA 1 2 1", "CZE 1 2 0", "NAM 1 2 0", "GRE 1 1 1", "HKG 1 1 1", "PLE 1 1 1", "BOL 1 1 0", "FSM 1 0 2", "POL 1 0 2", "SVK 1 0 2", "YEM 1 0 2", "HON 1 0 1", "PER 1 0 1", "ROM 1 0 1", "CGO 1 0 0", "GDR 1 0 0", "GUI 1 0 0", "THA 1 0 0", "ARM 0 3 0", "SAM 0 3 0", "INA 0 2 0", "IRL 0 1 2", "PLW 0 1 2", "ANG 0 1 1", "LIB 0 1 1", "VIE 0 1 1", "LAT 0 1 0", "LBA 0 1 0", "MON 0 1 0", "MYA 0 1 0", "TAN 0 1 0", "ARG 0 0 2", "DEN 0 0 2", "EST 0 0 2", "LUX 0 0 1", "MEX 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended7)
{
  auto data = std::vector<std::string>{"JOR NAM TUR", "TUN GRE SLO", "AUT KGZ JAM", "MKD SOM PAK", "URS BDI MKD", "MAR CAY URS", "COK CYP JAM", "HAI MKD SLO", "ARM COK MKD", "KGZ NAM RWA", "SLE BRN ITA", "RUS BHU SOM", "MTN COK HUN", "BDI SLE DEN", "SLO RUS HUN", "IRQ FIN MAR", "IRQ MKD SOM", "TCH VAN JAM", "RUS AZE POR", "HAI MYA HAI", "COK ITA MKD", "NAM DEN PUR", "MAR SRI VAN", "VAN ARG RWA", "ESP SMR MKD", "POR EST VAN", "EST POR MTN", "CRC NRU NAM", "PUR ISL PUR", "ITA SOM HAI", "SMR AZE SRI", "JAM RWA CAY", "DEN GRE AUT", "CYP HAI BDI", "AZE NAM VAN", "NRU HAI EST", "PAK PUR AUT", "HAI AND PUR"};
  auto expected = std::vector<std::string>{"HAI 3 2 2", "COK 2 2 0", "RUS 2 1 0", "MAR 2 0 1", "IRQ 2 0 0", "NAM 1 3 1", "MKD 1 2 4", "AZE 1 2 0", "PUR 1 1 3", "VAN 1 1 3", "BDI 1 1 1", "DEN 1 1 1", "EST 1 1 1", "ITA 1 1 1", "POR 1 1 1", "CYP 1 1 0", "KGZ 1 1 0", "NRU 1 1 0", "SLE 1 1 0", "SMR 1 1 0", "JAM 1 0 3", "AUT 1 0 2", "SLO 1 0 2", "MTN 1 0 1", "PAK 1 0 1", "URS 1 0 1", "ARM 1 0 0", "CRC 1 0 0", "ESP 1 0 0", "JOR 1 0 0", "TCH 1 0 0", "TUN 1 0 0", "SOM 0 2 2", "GRE 0 2 0", "RWA 0 1 2", "CAY 0 1 1", "SRI 0 1 1", "AND 0 1 0", "ARG 0 1 0", "BHU 0 1 0", "BRN 0 1 0", "FIN 0 1 0", "ISL 0 1 0", "MYA 0 1 0", "HUN 0 0 2", "TUR 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended8)
{
  auto data = std::vector<std::string>{"CAN COD GRN", "SUI SUI ISL", "IRI SUI GRN", "CRC AND LAT", "ANT IRI PUR", "KEN SOL ISL", "RWA PLE LBA", "FIN LIE DOM", "AHO SVK JPN", "MRI ECU PAK", "VEN GUY SOM", "GBR FIJ RWA", "SLO PLE PAN", "ECU TPE PUR", "PLE ANT ECU", "MAR LIE CHA", "BAN IRI SVK", "MRI PHI KEN", "SUI PUR IRI", "ISL LAT NIG", "COD KEN CAN", "ANT SUI ISL", "SVK PLE DJI", "MRI ARU DJI", "KEN SLO FIN", "PLE JPN SOM", "SVK MAD FRA", "SOM ECU CHA", "GRN CRO AHO", "SLO MAW LAT", "LUX PUR ARU", "OMA SUI TPE", "CHA RWA PAN", "GUY LAT PUR", "NIG AND MRI", "AHO SLO CRC", "SVK PUR PLE", "ECU OMA BAN", "ISV CAN EGY"};
  auto expected = std::vector<std::string>{"SVK 3 1 1", "MRI 3 0 1", "SUI 2 4 0", "PLE 2 3 1", "ECU 2 2 1", "SLO 2 2 0", "KEN 2 1 1", "ANT 2 1 0", "AHO 2 0 1", "IRI 1 2 1", "CAN 1 1 1", "RWA 1 1 1", "COD 1 1 0", "GUY 1 1 0", "OMA 1 1 0", "ISL 1 0 3", "CHA 1 0 2", "GRN 1 0 2", "SOM 1 0 2", "BAN 1 0 1", "CRC 1 0 1", "FIN 1 0 1", "NIG 1 0 1", "GBR 1 0 0", "ISV 1 0 0", "LUX 1 0 0", "MAR 1 0 0", "VEN 1 0 0", "PUR 0 3 3", "LAT 0 2 2", "AND 0 2 0", "LIE 0 2 0", "ARU 0 1 1", "JPN 0 1 1", "TPE 0 1 1", "CRO 0 1 0", "FIJ 0 1 0", "MAD 0 1 0", "MAW 0 1 0", "PHI 0 1 0", "SOL 0 1 0", "DJI 0 0 2", "PAN 0 0 2", "DOM 0 0 1", "EGY 0 0 1", "FRA 0 0 1", "LBA 0 0 1", "PAK 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended9)
{
  auto data = std::vector<std::string>{"VIE YEM VIE", "GUM FIJ RSA", "DMA CHI LAT", "AFG BAR VIE", "MOZ BAR ROM", "AHO BRA YEM", "ZIM BDI COK", "BOT PER BAR", "IRQ PER LCA", "VIE DOM NAM", "ETH CHN MAW", "EST ROM VIE", "AFG VIE CAM", "LIB ZIM DOM", "LIB PER FIJ", "EST ROM IRQ", "ETH RSA MAR", "KEN SUR FIJ", "LIB GER ARM", "CHI FIJ ETH", "TUR NAM LCA", "KEN VIE DOM", "KEN AFG DMA", "RSA LIB DOM", "AFG CAM VIE", "FIJ IRQ MOZ", "TJK SOM GRN", "KEN GEO ETH", "TJK ZIM PER", "VEN CAM BAR", "DMA BAR RSA", "SUR MOZ PER", "BRA CHN PER", "GER VEN ETH", "PER VEN IND", "MOZ ETH AHO", "FIJ COK SWE", "RUS RUS COK", "ARM MAW CHN", "SCG LIB GRN"};
  auto expected = std::vector<std::string>{"KEN 4 0 0", "LIB 3 2 0", "AFG 3 1 0", "VIE 2 2 4", "FIJ 2 2 2", "ETH 2 1 3", "MOZ 2 1 1", "DMA 2 0 1", "EST 2 0 0", "TJK 2 0 0", "PER 1 3 3", "VEN 1 2 0", "ZIM 1 2 0", "RSA 1 1 2", "IRQ 1 1 1", "BRA 1 1 0", "CHI 1 1 0", "GER 1 1 0", "RUS 1 1 0", "SUR 1 1 0", "AHO 1 0 1", "ARM 1 0 1", "BOT 1 0 0", "GUM 1 0 0", "SCG 1 0 0", "TUR 1 0 0", "BAR 0 3 2", "CAM 0 2 1", "CHN 0 2 1", "ROM 0 2 1", "DOM 0 1 3", "COK 0 1 2", "MAW 0 1 1", "NAM 0 1 1", "YEM 0 1 1", "BDI 0 1 0", "GEO 0 1 0", "SOM 0 1 0", "GRN 0 0 2", "LCA 0 0 2", "IND 0 0 1", "LAT 0 0 1", "MAR 0 0 1", "SWE 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended10)
{
  auto data = std::vector<std::string>{"SMR NOR LAO", "HKG LIE LIE", "KEN TPE RSA", "QAT HKG ITA", "UGA AFG ITA", "MDV RUS QAT", "SUI DOM PLW", "VIN NEP MAS", "SUI SWE UGA", "NEP VIN RUS", "MAR SUI KEN", "SYR COL SMR", "ISV MEX RWA", "AZE ESA AUS", "LAO DOM CAN", "SAM QAT SUI", "LIE MGL UGA", "COL MKD MRI", "MRI KGZ LAO", "MKD URS LAO", "GEQ LIE ESA", "QAT ISV ITA", "MAS PLW SWE", "FRG RUS AZE", "GEQ ECU GAB", "KEN TKM URS", "ESA KEN MGL", "ERI MAS AZE", "SAM CAN MAS", "DOM NOR MAS", "NEP TPE THA", "SWE NIG GAB", "ERI COL UGA", "CAN ISV RSA", "ERI NOR SWE", "MAS ARM SLO", "LIE GEQ ECU", "VIN MAR RSA", "COL FRG SUI", "NIG LIE MAS", "AZE AFG LAO"};
  auto expected = std::vector<std::string>{"ERI 3 0 0", "LIE 2 3 1", "COL 2 2 0", "MAS 2 1 4", "SUI 2 1 2", "KEN 2 1 1", "QAT 2 1 1", "GEQ 2 1 0", "NEP 2 1 0", "VIN 2 1 0", "AZE 2 0 2", "SAM 2 0 0", "DOM 1 2 0", "ISV 1 2 0", "SWE 1 1 2", "CAN 1 1 1", "ESA 1 1 1", "FRG 1 1 0", "HKG 1 1 0", "MAR 1 1 0", "MKD 1 1 0", "NIG 1 1 0", "LAO 1 0 4", "UGA 1 0 3", "MRI 1 0 1", "SMR 1 0 1", "MDV 1 0 0", "SYR 1 0 0", "NOR 0 3 0", "RUS 0 2 1", "AFG 0 2 0", "TPE 0 2 0", "ECU 0 1 1", "MGL 0 1 1", "PLW 0 1 1", "URS 0 1 1", "ARM 0 1 0", "KGZ 0 1 0", "MEX 0 1 0", "TKM 0 1 0", "ITA 0 0 3", "RSA 0 0 3", "GAB 0 0 2", "AUS 0 0 1", "RWA 0 0 1", "SLO 0 0 1", "THA 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended11)
{
  auto data = std::vector<std::string>{"BRA AHO CAY", "BRU LIE UGA", "CAM GAB BRU", "GER UAE GER", "MRI KGZ NCA", "GAM GUY MDA", "RSA LCA RSA", "BAR LTU BRU", "SMR AHO AHO", "HAI MDA MRI", "GUY NEP NEP", "MAW UAE JOR", "LTU CAM SOL", "RSA LCA PAN", "CPV GUY GUY", "BAR MRI RSA", "RSA LCA HKG", "MAW MDA BUL", "SOL LCA BUL", "SOL BAH SUR", "MAW HKG MLT", "JOR BRU MDA", "BAH RSA UGA", "SYR MGL LCA", "NEP UZB ARM", "CAY BRN NCA", "BAR UGA HKG", "KGZ LIE BRU", "MRI JPN MLT", "UAE GUY NCA", "SOL BRA CZE", "LIE LIE IRQ", "GER MGL ERI", "GAB MAW BAN", "UZB ISL BAR", "AHO MGL CAF", "RSA RSA BUL", "CZE IRQ PAN", "HAI CAM GER", "CAF CAF NEP", "BAH BRA UAE", "EUN NCA LIB"};
  auto expected = std::vector<std::string>{"RSA 4 2 2", "MAW 3 1 0", "BAR 3 0 1", "SOL 3 0 1", "MRI 2 1 1", "BAH 2 1 0", "GER 2 0 2", "HAI 2 0 0", "GUY 1 3 1", "LIE 1 3 0", "AHO 1 2 1", "UAE 1 2 1", "BRA 1 2 0", "CAM 1 2 0", "BRU 1 1 3", "NEP 1 1 2", "CAF 1 1 1", "GAB 1 1 0", "KGZ 1 1 0", "LTU 1 1 0", "UZB 1 1 0", "CAY 1 0 1", "CZE 1 0 1", "JOR 1 0 1", "CPV 1 0 0", "EUN 1 0 0", "GAM 1 0 0", "SMR 1 0 0", "SYR 1 0 0", "LCA 0 4 1", "MGL 0 3 0", "MDA 0 2 2", "NCA 0 1 3", "HKG 0 1 2", "UGA 0 1 2", "IRQ 0 1 1", "BRN 0 1 0", "ISL 0 1 0", "JPN 0 1 0", "BUL 0 0 3", "MLT 0 0 2", "PAN 0 0 2", "ARM 0 0 1", "BAN 0 0 1", "ERI 0 0 1", "LIB 0 0 1", "SUR 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended12)
{
  auto data = std::vector<std::string>{"SUI SRI URU", "FIJ LIE PAK", "IRQ UGA GAB", "PHI NIG AND", "MYA ITA URU", "AFG SIN FIJ", "UKR KSA AND", "GDR IRQ MKD", "GUM ANG NRU", "LBR NRU NZL", "ANG MAR KOR", "YEM SRI AND", "PHI ETH UKR", "YEM URU MTN", "ANG MKD YEM", "YEM MKD SOL", "GAB LIE GAB", "GUM SRI PAK", "TRI ECU PRK", "LIE PAK JAM", "ECU SIN AFG", "PAK SOL SRI", "PHI LBR AFG", "NIG LIE AFG", "FRG MKD MKD", "GDR MTN CUB", "AUS TRI PAK", "IRQ FIJ MAR", "CAY CMR PRK", "SUI PAK KEN", "GRE UGA ETH", "GRE NRU YEM", "CMR HON LIE", "CUB AND ANG", "ETH GAB NRU", "SIN MAR GDR", "UKR NZL CUB", "MYA BUR IRQ", "CMR ECU MAR", "UGA AND GAB", "HON INA ETH", "MTN PHI SUI", "NIG SWZ FRG"};
  auto expected = std::vector<std::string>{"PHI 3 1 0", "YEM 3 0 2", "ANG 2 1 1", "IRQ 2 1 1", "CMR 2 1 0", "NIG 2 1 0", "GDR 2 0 1", "SUI 2 0 1", "UKR 2 0 1", "GRE 2 0 0", "GUM 2 0 0", "MYA 2 0 0", "LIE 1 3 1", "PAK 1 2 3", "ECU 1 2 0", "SIN 1 2 0", "UGA 1 2 0", "GAB 1 1 3", "ETH 1 1 2", "FIJ 1 1 1", "MTN 1 1 1", "HON 1 1 0", "LBR 1 1 0", "TRI 1 1 0", "AFG 1 0 3", "CUB 1 0 2", "FRG 1 0 1", "AUS 1 0 0", "CAY 1 0 0", "MKD 0 3 2", "SRI 0 3 1", "AND 0 2 3", "MAR 0 2 2", "NRU 0 2 2", "URU 0 1 2", "NZL 0 1 1", "SOL 0 1 1", "BUR 0 1 0", "INA 0 1 0", "ITA 0 1 0", "KSA 0 1 0", "SWZ 0 1 0", "PRK 0 0 2", "JAM 0 0 1", "KEN 0 0 1", "KOR 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended13)
{
  auto data = std::vector<std::string>{"TLS EST ETH", "EGY BOT RWA", "CIV RWA FRA", "DJI PAK SWE", "CAM ALG ALG", "SWZ CRC ALG", "SOM POL PAK", "TUR VAN JOR", "MEX CAY AHO", "LCA ALG SRI", "OMA ZIM CRC", "ALG ERI ERI", "SWE GER CAM", "DJI NRU SRI", "CAY RWA TLS", "COL PHI CIV", "CRC KUW TLS", "TUR JOR SWZ", "GRN CAY AHO", "JOR PAK BAH", "GAB GEO CAM", "MDA GRN GAB", "TLS ETH SWZ", "BAH MDA LCA", "TLS PHI GBR", "SWZ TGA CIV", "ARU CIV PHI", "VAN CAM EGY", "SWZ MDA GEO", "TUR CHI CIV", "AHO KUW LCA", "CHI CIV BAH", "LCA CHI GER", "JOR CRC ARU", "BOT CIV RWA", "KEN ARU PHI", "PAK CAY TLS", "GHA BOT ALG", "PLW ALG NRU", "CRC VAN SRI", "GAB AHO GEO", "AHO CIV MEX", "CAY PLW POL", "KUW ECU ALG"};
  auto expected = std::vector<std::string>{"TLS 3 0 3", "SWZ 3 0 2", "TUR 3 0 0", "CAY 2 3 0", "CRC 2 2 1", "AHO 2 1 2", "JOR 2 1 1", "LCA 2 0 2", "GAB 2 0 1", "DJI 2 0 0", "CIV 1 4 3", "ALG 1 3 4", "PAK 1 2 1", "BOT 1 2 0", "CHI 1 2 0", "KUW 1 2 0", "MDA 1 2 0", "VAN 1 2 0", "CAM 1 1 2", "ARU 1 1 1", "GRN 1 1 0", "PLW 1 1 0", "BAH 1 0 2", "EGY 1 0 1", "MEX 1 0 1", "SWE 1 0 1", "COL 1 0 0", "GHA 1 0 0", "KEN 1 0 0", "OMA 1 0 0", "SOM 1 0 0", "PHI 0 2 2", "RWA 0 2 2", "GEO 0 1 2", "ERI 0 1 1", "ETH 0 1 1", "GER 0 1 1", "NRU 0 1 1", "POL 0 1 1", "ECU 0 1 0", "EST 0 1 0", "TGA 0 1 0", "ZIM 0 1 0", "SRI 0 0 3", "FRA 0 0 1", "GBR 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended14)
{
  auto data = std::vector<std::string>{"ROM SVK SRI", "FRA MDA BOL", "BAN CAF BOL", "FRA BAN NZL", "ITA GBR IND", "CAY VEN FIN", "BIH FIN IND", "VEN BAR IVB", "ARM MOZ CGO", "NAM MTN ERI", "QAT GEO BAR", "NAM PAR NAM", "SEY ROM SEY", "URS ASA TOG", "NRU MDA CGO", "VEN PRK CGO", "FRA TGA MGL", "PRK SVK PAK", "BLR TRI CGO", "IND MDV SRI", "NZL FIN CAY", "QAT THA THA", "GEO PUR PAR", "BOL PAK ROM", "ASA GAM FIN", "GEO FRA URU", "NRU NRU SRI", "BIH FRA PUR", "RSA MAS NZL", "ARU SVK CAF", "TOG MDV MDA", "BIH FIN KSA", "ARU NRU BIH", "PUR SRI SEY", "MDA THA BIH", "RSA CGO IVB", "RSA SRI ARU", "NAM URU IND", "GBR RSA SVK", "ALG SVK PRK", "CAF RSA CGO", "PUR TRI MDA", "BIH URU BIH", "FIN PUR URS", "BAN ERI THA"};
  auto expected = std::vector<std::string>{"BIH 4 0 3", "FRA 3 2 0", "RSA 3 2 0", "NAM 3 0 1", "PUR 2 2 1", "NRU 2 2 0", "BAN 2 1 0", "GEO 2 1 0", "VEN 2 1 0", "ARU 2 0 1", "QAT 2 0 0", "FIN 1 3 2", "MDA 1 2 2", "CAF 1 1 1", "PRK 1 1 1", "ROM 1 1 1", "ASA 1 1 0", "GBR 1 1 0", "IND 1 0 3", "BOL 1 0 2", "NZL 1 0 2", "SEY 1 0 2", "CAY 1 0 1", "TOG 1 0 1", "URS 1 0 1", "ALG 1 0 0", "ARM 1 0 0", "BLR 1 0 0", "ITA 1 0 0", "SVK 0 4 1", "SRI 0 2 3", "THA 0 2 2", "URU 0 2 1", "MDV 0 2 0", "TRI 0 2 0", "CGO 0 1 5", "BAR 0 1 1", "ERI 0 1 1", "PAK 0 1 1", "PAR 0 1 1", "GAM 0 1 0", "MAS 0 1 0", "MOZ 0 1 0", "MTN 0 1 0", "TGA 0 1 0", "IVB 0 0 2", "KSA 0 0 1", "MGL 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended15)
{
  auto data = std::vector<std::string>{"HAI BAH HAI", "TUR EST SIN", "FIN SUR CHA", "USA BAH GAB", "MAS AFG BOT", "CHA AFG MLI", "NCA USA SUI", "SEY LTU BRU", "EUN BAH CAM", "FIN USA ARM", "RSA GAB BUL", "COL FIN LES", "ARM SLE GUM", "CYP SEY LES", "PLW DOM LES", "SMR LTU MAS", "HAI CHA LES", "CZE YUG BAH", "ISV EST CAM", "NED SEY CAM", "RSA LES MTN", "THA SIN ALB", "HAI SUI SUI", "THA BRU MTN", "HAI SUR YUG", "USA PLW MAS", "LES CHA RSA", "ANG LES SEY", "CAM YUG CAM", "EUN NCA TKM", "MAS GAB KOR", "CAM CYP CYP", "CPV SIN BRU", "BAH PAR CZE", "PAK BUL CHN", "PAR BUL TKM", "CYP NGR BOT", "ARM RSA NGR", "SUI USA NGR", "AFG EUN DOM", "TKM YUG RSA", "GUM CHA ARM", "RSA GUM SUI", "SUR LBR LTU", "CHN CPV PLW", "GAB TUR SUR"};
  auto expected = std::vector<std::string>{"HAI 4 0 1", "RSA 3 1 2", "USA 2 3 0", "CYP 2 1 1", "EUN 2 1 0", "FIN 2 1 0", "CAM 2 0 4", "ARM 2 0 2", "MAS 2 0 2", "THA 2 0 0", "BAH 1 3 1", "CHA 1 3 1", "LES 1 2 4", "GAB 1 2 1", "SEY 1 2 1", "SUR 1 2 1", "AFG 1 2 0", "SUI 1 1 3", "GUM 1 1 1", "PLW 1 1 1", "CPV 1 1 0", "NCA 1 1 0", "PAR 1 1 0", "TUR 1 1 0", "TKM 1 0 2", "CHN 1 0 1", "CZE 1 0 1", "ANG 1 0 0", "COL 1 0 0", "ISV 1 0 0", "NED 1 0 0", "PAK 1 0 0", "SMR 1 0 0", "YUG 0 3 1", "BUL 0 2 1", "LTU 0 2 1", "SIN 0 2 1", "EST 0 2 0", "BRU 0 1 2", "NGR 0 1 2", "DOM 0 1 1", "LBR 0 1 0", "SLE 0 1 0", "BOT 0 0 2", "MTN 0 0 2", "ALB 0 0 1", "KOR 0 0 1", "MLI 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended16)
{
  auto data = std::vector<std::string>{"QAT TLS CAF", "THA CRO LIB", "MGL ARM CYP", "MRI ARM BLR", "ASA TLS CRO", "CHN ALG LIE", "ARM ASA IRI", "RSA BLR NIG", "VIN CHN CRO", "VIN PAK DEN", "AUS LIE CRO", "DEN KOR KOR", "SMR AUS LIB", "AUS QAT LTU", "DOM SMR LES", "LIE ARM LIE", "AUS AUS MGL", "LES TLS RSA", "CHN SWZ ALG", "JPN SMR RSA", "PLE TLS HAI", "YEM CYP SUR", "LES AUS VIN", "ARG CHN PAK", "MRI KOR MDV", "CAF ARM NEP", "OMA BEN PAK", "GUA NIG OMA", "CAF TLS MGL", "CAF HAI LES", "ARG BLR JPN", "INA BOL NZL", "DOM NEP QAT", "DOM OMA ARM", "ASA GUY LIB", "MRI LIE MGL", "GUA GEO PAK", "AUS NEP IRI", "SMR SWZ GUA", "LES BAH PLE", "ALG BLR USA", "JPN LIE BLR", "CAF SUR SMR", "ALG BLR LTU", "ARM CHN USA", "MON SWZ LIB", "CRO CRO SMR"};
  auto expected = std::vector<std::string>{"AUS 4 3 0", "CAF 4 0 1", "LES 3 0 2", "DOM 3 0 0", "MRI 3 0 0", "ARM 2 4 1", "CHN 2 3 0", "SMR 2 2 2", "ALG 2 1 1", "ASA 2 1 0", "GUA 2 0 1", "JPN 2 0 1", "VIN 2 0 1", "ARG 2 0 0", "LIE 1 3 2", "CRO 1 2 3", "OMA 1 1 1", "QAT 1 1 1", "MGL 1 0 3", "RSA 1 0 2", "DEN 1 0 1", "PLE 1 0 1", "INA 1 0 0", "MON 1 0 0", "THA 1 0 0", "YEM 1 0 0", "TLS 0 5 0", "BLR 0 4 2", "SWZ 0 3 0", "KOR 0 2 1", "NEP 0 2 1", "PAK 0 1 3", "CYP 0 1 1", "HAI 0 1 1", "NIG 0 1 1", "SUR 0 1 1", "BAH 0 1 0", "BEN 0 1 0", "BOL 0 1 0", "GEO 0 1 0", "GUY 0 1 0", "LIB 0 0 4", "IRI 0 0 2", "LTU 0 0 2", "USA 0 0 2", "MDV 0 0 1", "NZL 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended17)
{
  auto data = std::vector<std::string>{"SCG ZIM TPE", "KUW MGL NIG", "ANT VIE RUS", "GHA VAN YUG", "UAE RUS BOT", "BOT AUS VIN", "AUS BUL CAM", "INA TUN SIN", "STP GHA VAN", "NOR STP RWA", "VEN MGL SCG", "SKN VAN CHI", "IND VIE CAM", "VIN CAN ZIM", "VIN AHO RWA", "AUS BOT STP", "AHO CAM UAE", "CAM LUX SEY", "TUN GRE VEN", "STP TCH RWA", "MON SIN CHI", "FIJ NEP AUS", "IND TUN AHO", "KUW TPE FIJ", "MGL STP FIJ", "CHI TPE GRE", "VEN TPE IVB", "TPE VIN TUN", "NCA TUN BOT", "MON NRU VAN", "FIJ AUS RWA", "ISL GHA FRG", "KUW NIG AHO", "MGL AHO TPE", "PLW NAM PLW", "STP ROM LUX", "ZIM NRU HKG", "KOR KOR GRE", "GUA VIE BUL", "ISR KOR RWA", "GUA NOR SKN", "VEN VIE AHO", "BUL ISL NRU", "CAN STP NRU", "VIE IVB CAM", "NRU FIJ SKN", "AHO CHI IVB", "IND NOR SKN"};
  auto expected = std::vector<std::string>{"STP 3 3 1", "VEN 3 0 1", "IND 3 0 0", "KUW 3 0 0", "AHO 2 2 3", "AUS 2 2 1", "MGL 2 2 0", "FIJ 2 1 2", "VIN 2 1 1", "GUA 2 0 0", "MON 2 0 0", "VIE 1 4 0", "TPE 1 3 2", "TUN 1 3 1", "NRU 1 2 2", "GHA 1 2 0", "KOR 1 2 0", "NOR 1 2 0", "CAM 1 1 3", "BOT 1 1 2", "CHI 1 1 2", "BUL 1 1 1", "ZIM 1 1 1", "CAN 1 1 0", "ISL 1 1 0", "SKN 1 0 3", "PLW 1 0 1", "SCG 1 0 1", "UAE 1 0 1", "ANT 1 0 0", "INA 1 0 0", "ISR 1 0 0", "NCA 1 0 0", "VAN 0 2 2", "GRE 0 1 2", "IVB 0 1 2", "LUX 0 1 1", "NIG 0 1 1", "RUS 0 1 1", "SIN 0 1 1", "NAM 0 1 0", "NEP 0 1 0", "ROM 0 1 0", "TCH 0 1 0", "RWA 0 0 5", "FRG 0 0 1", "HKG 0 0 1", "SEY 0 0 1", "YUG 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended18)
{
  auto data = std::vector<std::string>{"MAR LTU JOR", "MRI IRQ MDV", "LAT MAW SVK", "MRI BUR QAT", "USA BUR JOR", "KOR MEX ASA", "MYA NZL IRQ", "EUN IND ARU", "KOR CAN SWE", "STP ETH FRG", "TCH STP STP", "IRQ MDV FRG", "BDI BOL TAN", "TJK QAT BOT", "PER STP FRG", "CHN FRG ALG", "EUN BDI NZL", "PUR IRQ BUR", "QAT TAN JOR", "PAK SKN PAK", "BEN PER MLI", "ALG DEN ESA", "FRG FRG IRI", "EUN ETH ETH", "KOR BIH BOT", "QAT IND LAT", "QAT PAK MAW", "MEX MAR ARU", "PUR GUY TCH", "DEN BUR QAT", "ASA EUN MLI", "NCA EUN SWE", "ALG MYA ESA", "JOR ARU MAW", "PAK MAD NZL", "TAN GBS BOL", "JOR CHN SWE", "BDI STP LAT", "BOL MYA TAN", "BEN USA BEN", "TJK BAR JOR", "MEX PER PER", "LTU QAT MAD", "QAT ESA MDV", "IRQ BEN BOT", "CAF ARU LTU", "GUY MAD PUR", "ETH MEX MON", "SKN PER GUY"};
  auto expected = std::vector<std::string>{"QAT 4 2 2", "EUN 3 2 0", "KOR 3 0 0", "IRQ 2 2 1", "MEX 2 2 0", "BEN 2 1 1", "PAK 2 1 1", "BDI 2 1 0", "JOR 2 0 4", "ALG 2 0 1", "PUR 2 0 1", "MRI 2 0 0", "TJK 2 0 0", "PER 1 3 1", "STP 1 3 1", "FRG 1 2 3", "ETH 1 2 1", "MYA 1 2 0", "TAN 1 1 2", "BOL 1 1 1", "GUY 1 1 1", "LTU 1 1 1", "CHN 1 1 0", "DEN 1 1 0", "MAR 1 1 0", "SKN 1 1 0", "USA 1 1 0", "LAT 1 0 2", "ASA 1 0 1", "TCH 1 0 1", "CAF 1 0 0", "NCA 1 0 0", "BUR 0 3 1", "ARU 0 2 2", "MAD 0 2 1", "IND 0 2 0", "ESA 0 1 2", "MAW 0 1 2", "MDV 0 1 2", "NZL 0 1 2", "BAR 0 1 0", "BIH 0 1 0", "CAN 0 1 0", "GBS 0 1 0", "BOT 0 0 3", "SWE 0 0 3", "MLI 0 0 2", "IRI 0 0 1", "MON 0 0 1", "SVK 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended19)
{
  auto data = std::vector<std::string>{"UKR ANT IRQ", "HUN BRU IRI", "BER LES GUM", "HUN KEN PAR", "GUM SRI ETH", "IRI CHN OMA", "IRI ANT HAI", "SWE GER PLW", "UKR ETH CIV", "UKR HKG MAR", "COK GER MYA", "PRK VAN SCG", "ETH ALG GUM", "SRI HUN BOL", "MLT ALG VAN", "ANT ITA CAN", "PAK BOL CIV", "CIV ANT MAR", "ANT VAN ARG", "EGY SRI IRI", "ALG CAN VIE", "PAK ALG VIE", "KEN FRG VIE", "BOL CIV IRI", "CAN VAN ITA", "BRU YEM CAN", "COK OMA CPV", "IRQ ANT CYP", "CGO BOL CPV", "CIV GER CHA", "PRK GER ETH", "RSA BUR GRN", "PLW PLW PRK", "PLW SRI BOL", "ERI BER ANT", "VAN CAN ARG", "BRU HAI RSA", "GUM ANT SCG", "PLW CIV UKR", "BOL IRI FRG", "EGY FRG PLW", "MRI CHA YEM", "BRU ANT PRK", "VAN SCG MLT", "BER CIV PAR", "BUR CHN UKR", "CHN FRG GRN", "ARG RSA HKG", "UKR LES PAK", "SRI OMA CYP"};
  auto expected = std::vector<std::string>{"UKR 4 0 2", "PLW 3 1 2", "BRU 3 1 0", "ANT 2 6 1", "CIV 2 3 2", "VAN 2 3 1", "SRI 2 3 0", "BOL 2 2 2", "IRI 2 1 3", "BER 2 1 0", "HUN 2 1 0", "GUM 2 0 2", "PRK 2 0 2", "PAK 2 0 1", "COK 2 0 0", "EGY 2 0 0", "ALG 1 3 0", "CAN 1 2 2", "CHN 1 2 0", "ETH 1 1 2", "RSA 1 1 1", "BUR 1 1 0", "KEN 1 1 0", "ARG 1 0 2", "IRQ 1 0 1", "MLT 1 0 1", "CGO 1 0 0", "ERI 1 0 0", "MRI 1 0 0", "SWE 1 0 0", "GER 0 4 0", "FRG 0 3 1", "OMA 0 2 1", "LES 0 2 0", "SCG 0 1 2", "CHA 0 1 1", "HAI 0 1 1", "HKG 0 1 1", "ITA 0 1 1", "YEM 0 1 1", "VIE 0 0 3", "CPV 0 0 2", "CYP 0 0 2", "GRN 0 0 2", "MAR 0 0 2", "PAR 0 0 2", "MYA 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended20)
{
  auto data = std::vector<std::string>{"ARM NOR AND", "CGO MAW PUR", "CGO ARM NOR", "PUR ARM BHU", "BHU ARM BHU", "ARM MAW PUR", "CGO CGO NOR", "CGO BHU CGO", "MAW AND PUR", "NOR MAW CGO", "NOR NOR BHU", "NOR BHU AND", "NOR NOR ARM", "CGO NOR BIH", "NOR AND CGO", "ARM BHU ARM", "AND NOR NOR", "NOR BHU AND", "BHU PUR AND", "ARM MAW MAW", "MAW CGO CGO", "AND BHU NOR", "AND AND MAW", "ARM MAW BIH", "CGO BIH BIH", "AND CGO MAW", "BHU CGO BIH", "AND BHU NOR", "AND CGO MAW", "AND NOR BIH", "NOR BIH PUR", "BHU BIH ARM", "AND BIH BHU", "MAW MAW PUR", "AND ARM BHU", "CGO BHU PUR", "ARM CGO BIH", "MAW CGO NOR", "BIH CGO BHU", "AND CGO AND", "BIH BHU CGO", "BHU CGO PUR", "CGO MAW BIH", "NOR BHU AND", "MAW BIH ARM", "PUR PUR BIH"};
  auto expected = std::vector<std::string>{"AND 10 3 6", "CGO 8 10 5", "NOR 8 6 6", "ARM 6 4 4", "BHU 5 9 6", "MAW 5 7 4", "BIH 2 5 8", "PUR 2 2 7"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended21)
{
  auto data = std::vector<std::string>{"MDV FIJ ASA", "GDR FRG GDR", "HON MDV MDV", "FRG HON FRG", "AFG ASA ASA", "FIJ ASA HON", "GER FRG GER", "GDR HON GDR", "GER HON HON", "FIJ ASA HON", "FRG ASA AFG", "GDR GER FRG", "AFG FRG FIJ", "MDV HON ASA", "FIJ HON FIJ", "FRG ASA GDR", "ASA HON MDV", "MDV FRG GER", "FRG AFG FRG", "ASA FIJ GER", "MDV GER HON", "MDV ASA FRG", "FRG FIJ HON", "GER ASA GER", "HON GDR FRG", "ASA MDV GDR", "GER ASA FRG", "GDR AFG HON", "ASA FRG HON", "GER GDR AFG", "FIJ FRG HON", "AFG FIJ MDV", "FRG GER ASA", "ASA FRG FRG", "HON ASA MDV", "FIJ FIJ HON", "HON MDV MDV", "ASA FRG MDV", "MDV GER FIJ", "GER FIJ HON", "HON GDR ASA", "GDR GDR GDR", "FRG MDV ASA", "GER AFG GDR", "AFG MDV HON", "MDV ASA AFG", "GER MDV AFG"};
  auto expected = std::vector<std::string>{"GER 8 4 4", "FRG 7 8 7", "MDV 7 6 6", "ASA 6 10 6", "HON 5 6 11", "FIJ 5 6 3", "GDR 5 4 6", "AFG 4 3 4"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended22)
{
  auto data = std::vector<std::string>{"GRE LUX LES", "SLO SWZ BER", "GRE JAM JAM", "CMR LES BER", "GRE CMR BER", "CMR SWZ SWZ", "GRE SWZ LUX", "CMR SWZ GRE", "GRE JAM SLO", "JAM JAM LUX", "CMR SLO JAM", "LUX LES GRE", "LUX SWZ LUX", "BER BER CMR", "CMR GRE GRE", "CMR JAM CMR", "CMR LUX CMR", "SLO SWZ BER", "BER CMR JAM", "SLO LES SWZ", "LES LUX LUX", "SWZ GRE CMR", "CMR SWZ BER", "SLO BER CMR", "SWZ CMR JAM", "GRE GRE SWZ", "JAM JAM LES", "LES CMR JAM", "LUX CMR LUX", "BER BER CMR", "SWZ LES SWZ", "LES JAM CMR", "SLO LES CMR", "SLO GRE CMR", "SWZ CMR GRE", "JAM JAM LES", "GRE SWZ BER", "SLO JAM CMR", "GRE BER JAM", "SWZ CMR JAM", "BER BER SWZ", "SWZ LUX GRE", "CMR JAM SLO", "GRE CMR BER", "JAM CMR CMR", "LUX LES LUX", "CMR SLO LES", "CMR LES SWZ"};
  auto expected = std::vector<std::string>{"CMR 11 9 11", "GRE 9 4 5", "SLO 7 2 2", "SWZ 6 8 6", "JAM 4 9 7", "BER 4 5 7", "LUX 4 4 6", "LES 3 7 4"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended23)
{
  auto data = std::vector<std::string>{"CGO AFG MON", "NGR CHA NGR", "CGO AFG AFG", "GUY AFG GUY", "HON CGO AFG", "AFG NGR CHA", "NGR CHA GUY", "CHA CHA NGR", "CGO CHA HON", "NGR GUY MON", "HON HON MON", "CHA GUY SWE", "AFG HON SWE", "CGO SWE SWE", "HON GUY CGO", "MON GUY SWE", "SWE CGO CHA", "CHA HON HON", "CGO MON NGR", "MON GUY CGO", "GUY AFG MON", "AFG CHA AFG", "AFG CHA MON", "SWE GUY HON", "SWE AFG AFG", "AFG MON GUY", "SWE HON MON", "CGO NGR CGO", "MON SWE NGR", "GUY MON CGO", "HON AFG CGO", "CHA AFG GUY", "CHA AFG NGR", "SWE AFG CGO", "HON SWE CGO", "HON SWE NGR", "SWE NGR CHA", "HON AFG CGO", "MON MON AFG", "GUY CGO MON", "MON MON MON", "NGR SWE NGR", "CHA CHA NGR", "AFG CGO NGR", "CGO MON MON", "GUY CGO HON", "CGO CGO GUY", "HON MON GUY", "MON GUY AFG"};
  auto expected = std::vector<std::string>{"CGO 8 6 8", "HON 8 4 4", "AFG 6 10 6", "MON 6 7 9", "CHA 6 7 3", "SWE 6 5 4", "GUY 5 7 6", "NGR 4 3 9"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended24)
{
  auto data = std::vector<std::string>{"SUI SUI KEN", "BRU SLO KEN", "FRA GUM SLO", "UKR COK BRU", "COK SLO FRA", "FRA BRU SUI", "UKR GUM GUM", "FRA KEN BRU", "COK SLO GUM", "KEN KEN KEN", "SUI GUM FRA", "FRA GUM UKR", "SUI SLO GUM", "KEN SLO KEN", "KEN SUI COK", "SUI BRU FRA", "KEN UKR SLO", "UKR FRA COK", "BRU GUM UKR", "GUM UKR GUM", "UKR SUI SUI", "FRA BRU FRA", "COK UKR UKR", "KEN GUM KEN", "BRU UKR FRA", "FRA SUI FRA", "KEN FRA FRA", "COK FRA KEN", "GUM FRA UKR", "FRA SLO SUI", "SLO SLO KEN", "KEN UKR SLO", "SUI BRU KEN", "SLO SLO UKR", "FRA SLO SUI", "KEN UKR KEN", "UKR GUM UKR", "COK SLO COK", "SLO BRU GUM", "KEN FRA BRU", "FRA UKR SLO", "UKR GUM KEN", "KEN COK SLO", "BRU UKR FRA", "UKR COK UKR", "SLO SLO UKR", "FRA KEN FRA", "COK SLO UKR", "FRA FRA UKR", "SLO SUI COK"};
  auto expected = std::vector<std::string>{"FRA 11 6 9", "KEN 10 3 10", "UKR 7 8 10", "COK 6 3 4", "SLO 5 12 5", "SUI 5 5 4", "BRU 4 5 3", "GUM 2 8 5"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended25)
{
  auto data = std::vector<std::string>{"CCC AAA BBB", "AAA BBB CCC", "BBB CCC AAA", "DDD EEE FFF", "DDD EEE FFF", "DDD EEE FFF"};
  auto expected = std::vector<std::string>{"DDD 3 0 0", "AAA 1 1 1", "BBB 1 1 1", "CCC 1 1 1", "EEE 0 3 0", "FFF 0 0 3"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended26)
{
  auto data = std::vector<std::string>{"AAA BBB CCC", "BBB CCC DDD", "DDD EEE FFF", "FFF GGG HHH", "III JJJ MMM", "MMM MMM ZZZ", "AAA EEE VVV", "VVV VVV BBB", "CCC CCC CCC", "ZZZ ZZZ LLL", "AVC ABC ABG", "PPP OOO LLL", "RRR TTT SSS", "SSS WWW QQQ", "MNO PQR STU", "FGH JJJ BBB", "CCC DDD VVV", "AAA ZZZ WWW", "EEE WWW TTT", "TTT YYY UUU", "LLL MMM JJJ", "LLL LLL OOO", "BBB VVV DDD", "EEE WWW RRR", "OLM NPO TRS", "LJG FTR SSS", "VVV BBB NNN", "WER REW RRR", "TTT YYY UUU", "QQQ QQQ SSS", "LLL MMM NNN", "FFF RRR TTT", "PPP PPP PPP", "TTT YYY UUU", "JJJ GGG MMM", "CCC ZZZ YTR", "ASD DFG FGH", "LLL MMM VVV", "BBB NNN HHH", "PPP PPP PPP", "EEE RTY YUI", "PLK JHG FDS", "MBA PHD MBA", "CCC BBB AAA", "AAA BBB VVV", "CCC SSS AAA", "PPP LLL OOO", "TTT YYY UUU", "AAA AAA VVV", "LLL OOO PPP"};
  auto expected = std::vector<std::string>{"CCC 5 2 2", "LLL 5 2 2", "AAA 5 1 2", "PPP 4 2 3", "TTT 4 1 2", "BBB 3 4 2", "EEE 3 2 0", "VVV 2 2 5", "FFF 2 0 1", "MMM 1 4 2", "ZZZ 1 3 1", "JJJ 1 2 1", "SSS 1 1 3", "DDD 1 1 2", "RRR 1 1 2", "QQQ 1 1 1", "FGH 1 0 1", "MBA 1 0 1", "ASD 1 0 0", "AVC 1 0 0", "III 1 0 0", "LJG 1 0 0", "MNO 1 0 0", "OLM 1 0 0", "PLK 1 0 0", "WER 1 0 0", "YYY 0 4 0", "WWW 0 3 1", "OOO 0 2 2", "GGG 0 2 0", "NNN 0 1 2", "ABC 0 1 0", "DFG 0 1 0", "FTR 0 1 0", "JHG 0 1 0", "NPO 0 1 0", "PHD 0 1 0", "PQR 0 1 0", "REW 0 1 0", "RTY 0 1 0", "UUU 0 0 4", "HHH 0 0 2", "ABG 0 0 1", "FDS 0 0 1", "STU 0 0 1", "TRS 0 0 1", "YTR 0 0 1", "YUI 0 0 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended27)
{
  auto data = std::vector<std::string>{"GER AUT SUI", "AUT SUI GER", "SUI GER AUT"};
  auto expected = std::vector<std::string>{"AUT 1 1 1", "GER 1 1 1", "SUI 1 1 1"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended28)
{
  auto data = std::vector<std::string>{"GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI", "GER AUT SUI"};
  auto expected = std::vector<std::string>{"GER 13 0 0", "AUT 0 13 0", "SUI 0 0 13"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended29)
{
  auto data = std::vector<std::string>{"GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB", "GGG SSS BBB"};
  auto expected = std::vector<std::string>{"GGG 13 0 0", "SSS 0 13 0", "BBB 0 0 13"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended30)
{
  auto data = std::vector<std::string>{"AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC", "AAA BBB CCC"};
  auto expected = std::vector<std::string>{"AAA 12 0 0", "BBB 0 12 0", "CCC 0 0 12"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended31)
{
  auto data = std::vector<std::string>{"ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ITA ITA ITA", "ABC ABC ABC", "ABC ABC ABC"};
  auto expected = std::vector<std::string>{"ITA 11 11 11", "ABC 2 2 2"};
  ASSERT_EQ(expected, medal_table(data));
}
TEST(TEST_NAME, Extended32)
{
  auto data = std::vector<std::string>{"AUS CHN AUT", "USA CHN AUT", "USA CHN AUT", "USA CHN AUT", "USA CHN AUT", "USA CHN AUT", "USA CHN AUT", "USA CHN AUT", "USA CHN AUT", "USA CHN AUT", "USA CHN AUT"};
  auto expected = std::vector<std::string>{"USA 10 0 0", "AUS 1 0 0", "CHN 0 11 0", "AUT 0 0 11"};
  ASSERT_EQ(expected, medal_table(data));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
