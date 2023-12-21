#pragma once

#include "Yakreb/Core/Core.h"

#include <string>
#include <map>

namespace Yakreb {

	enum class ControllerType : uint8_t {
		None = 0,
		Unmapped = 1,
		Generic,
		Apple,
		AstroCity,
		Dreamcast,
		EightBitDo,
		GameCube,
		Luna,
		MobileTouch,
		N64,
		NeoGeo,
		Ouya,
		PCEngine,
		PlayStation1,
		PlayStation3,
		PlayStation4,
		PlayStation5,
		SNES,
		Saturn,
		Stadia,
		Steam,
		SteamV2,
		SuperFamicom,
		Switch,
		SwitchJoyConLeft,
		SwitchJoyConRight,
		SwitchLike,
		SwitchPro,
		WiiRemote,
		XBox360,
		XBoxLike,
		XBoxOne
	};

	enum class ButtonState : uint8_t {
		None = 0,
		Released,
		Pressed,
		Held
	};

	enum class HatState : uint8_t {
		None = 0,
		Centered = 0,
		Up = BIT(0),
		Right = BIT(1),
		Down = BIT(2),
		Left = BIT(3),
		UpRight = Right | Up,
		UpLeft = Left | Up,
		DownRight = Right | Down,
		DownLeft = Left | Down
	};

	struct Controller {
		int ID;
		std::string Name;
		ControllerType Type;
		bool UseAsGamePad;
		std::map<int, ButtonState> ButtonStates;
		std::map<int, float> AxisStates;
		std::map<int, float> AxisDeadZones;
		std::map<int, HatState> HatStates;
	};

	constexpr const char* GetButtonStateName(const ButtonState buttonstate) {
		switch (buttonstate) {
			case ButtonState::None:     return "None";
			case ButtonState::Released: return "Released";
			case ButtonState::Pressed:  return "Pressed";
			case ButtonState::Held:     return "Held";
		}

		YGE_CORE_DEBUG_WARN("Invalid ButtonState({})!", static_cast<int>(buttonstate));
		return "";
	}

	constexpr const char* GetHatStateName(const HatState hatstate) {
		switch (hatstate) {
			case HatState::Centered:  return "Centered";
			case HatState::Up:        return "Up";
			case HatState::Right:     return "Right";
			case HatState::Down:      return "Down";
			case HatState::Left:      return "Left";
			case HatState::UpRight:   return "Up-Right";
			case HatState::UpLeft:    return "Up-Left";
			case HatState::DownRight: return "Down-Right";
			case HatState::DownLeft:  return "Down-Left";
		}

		YGE_CORE_DEBUG_WARN("Invalid HatState({})!", static_cast<int>(hatstate));
		return "";
	}

	namespace detail {
		class Controller {
			public:
				// Data taken from https://github.com/offalynne/Input/blob/dev_4.2_LTS/datafiles/controllertypes.csv
				inline const static std::map<const ControllerType, const std::vector<const char*>> controllerTypeMap = {
					{ ControllerType::Apple, { "ac050100", "ac050200" } },
					{ ControllerType::AstroCity, { "a30c2700", "a30c2800" } },
					{ ControllerType::Dreamcast, { "9b280800" } },
					{ ControllerType::EightBitDo, { "02100090", "351212ab", "35124028", "02200090", "c82d2028", "c82d4028", "c82d6228", "c82d0030", "c82d0130", "c82d0451", "c82d1290", "c82d20ab", "c82d0160", "c82d6528", "c82d1038", "c82d2038", "c82d0060", "c82d0260", "c82d0161", "c82d0261", "c82d9000", "c82d0190", "c82d1590", "c82d3032", "20380900", "10380900", "c82d0360", "c82d0361", "c82d0660" } },
					{ ControllerType::GameCube, { "7e053703", "26098888", "79004318", "79004518", "79004618", "79004718", "430b0500", "341a05f7" } },
					{ ControllerType::Luna, { "71011904" } },
					{ ControllerType::MobileTouch, { "0000fb11" } },
					{ ControllerType::N64, { "7e051920", "f7060100", "c82d0290", "c82d3038" } },
					{ ControllerType::NeoGeo, { "9212474e" } },
					{ ControllerType::Ouya, { "36280100" } },
					{ ControllerType::PCEngine, { "0d0f3801" } },
					{ ControllerType::PlayStation1, { "4f0423b3", "4f0403d0", "4f0408d0", "4f0409d0", "6d04d1ca", "4c053713", "a3062106", "a30620f6", "a30623f6", "38078731", "38078232", "38078433", "38078034", "38078134", "38076382", "38071888", "380756a8", "120c1307", "120c1cf1", "6f0e1401", "6f0e1901", "6f0e1a01", "6f0e2f01", "6f0e3001", "6f0e3201", "8f0e1431", "0d0f1000", "0d0f1100", "0d0f1300", "0d0f2100", "0d0f2200", "0d0f2600", "0d0f2700", "0d0f2d00", "0d0f2500", "0d0f3200", "0d0f3d00", "0d0f4000", "0d0f4200", "0d0f4900", "0d0f4b00", "0d0f5100", "0d0f5400", "0d0f6400", "300f1611", "c0110355", "120cf90e", "d81407cd", "32150204", "7c180006", "341a0302", "4f1f0800", "d6206000", "d6209f31", "d6201d57", "d6209557", "d620c757", "d620e557", "f025c183", "222c0223", "6e050520", "6e050620", "300f1211", "4f0420b3", "4f0401d0", "88880804", "504c5354", "ff00cb01", "83055020", "830531b0", "9d0d1330", "300f1210", "6b140203", "6b140303", "addeefbe", "0d0f3701", "6b140103", "63252306", "c82d0751", "d9040200", "d904160f", "4c05da0c", "e3059605", "25090118", "25090088", "25096888", "ba220701", "430b0300", "8f0e0000", "8f0e0300", "8f0e0910", "ff114133", "bd1201e0", "bd1202e0", "f025c283", "f025c483", "66666706", "66660488", "5f143102" } },
					{ ControllerType::PlayStation3, { "79001a18", "79004418", "4f0415b3", "4f0407d0", "4c056802", "6e050f20", "6e051320", "b8050410", "b8050610", "a30622f6", "38078031", "38075032", "38078081", "38073888", "10080100", "10080300", "25090500", "25096688", "25098888", "6f0e0901", "6f0e1e01", "6f0e2801", "6f0e0302", "6f0e1402", "6f0e1413", "6f0e0263", "8f0e0800", "8f0e7530", "8f0e0d31", "0d0f0900", "0d0f4d00", "0d0f5e00", "0d0f5f00", "0d0f6a00", "0d0f6e00", "0d0f8500", "0d0f8600", "0d0f8700", "300f0011", "ff113133", "45130010", "45130560", "6b140306", "6b140055", "341a3608", "bc200055", "d6206d57", "d6206dca", "63252305", "63257505", "f025c383", "f02521c1", "222c0020", "222c0320", "80830300", "88880803" } },
					{ ControllerType::PlayStation4, { "79001b18", "4c05c405", "4c05c505", "4c05cc09", "4c05a00b", "38075082", "38078483", "38078084", "38078184", "120c100e", "120cf61c", "120c150e", "120cf60e", "0d0f5500", "0d0f6600", "0d0f8400", "0d0f8a00", "0d0f9c00", "0d0fa000", "0d0fee00", "c0110140", "6b14010d", "6b14020d", "32150104", "32150010", "32150410", "32150710", "32150810", "32150910", "32150a10", "32150011", "d6202a79", "45750401", "86982500", "6f0e0702", "45752211", "4f040ed0", "120c101e", "6b14090d", "6b14100d", "6b14080d", "6b14060d", "6b140311", "0d0f2301", "6b14130d", "120c200e", "222c0023", "952e2577", "120c0807", "120c110e", "120c130e", "120c160e", "120c180e", "120c1e0e", "120cf10e", "120cf70e", "120cf21c", "120cf31c", "120cf41c", "120cf51c", "120c111e", "120c121e", "120c181e", "120c191e", "120c1c1e", "120ca857", "120ca957", "120caa57", "120cab57", "120c210e", "38078532" } },
					{ ControllerType::PlayStation5, { "4c05e60c" } },
					{ ControllerType::SNES, { "9b285600", "9b285700", "00f00300", "00f0f100", "0304c197", "92124653", "81179d0a", "8b280300", "9b280300", "79000418", "280d0202", "03000300", "1104c600", "100801e5", "8f0e1330", "bd1215d0", "351220ab", "c82d0351", "8117960a", "000f0100", "92124346", "571d2100", "c82de002", "9b280200", "5448434d" } },
					{ ControllerType::Saturn, { "490b4406", "79001100", "9b280500", "81177e05", "fd055302", "fd050030", "79002201", "83056020", "79002418", "7900ae18", "5e040300", "5e040700", "5e040e00", "5e042600", "5e042700", "6d0409c2", "6d040ac2", "6d0411c2", "7d040340", "b4040a01", "83055130", "73070601", "8f0e4100", "8f0e1030", "bd1213d0", "9b284300", "c82d5106", "c82d0650", "c82d2867", "c82d0150", "c82d0151", "00f00800", "c016990a", "a30c2400", "a30c2500" } },
					{ ControllerType::Stadia, { "d1180094" } },
					{ ControllerType::Steam, { "de280111", "de280211", "de280511", "de280611", "de284211", "de28ff11" } },
					{ ControllerType::SteamV2, { "de280112", "de280212" } },
					{ ControllerType::SuperFamicom, { "1f0801e4", "351221ab", "10280900", "c82d3028", "c82d21ab", "c82d1028" } },
					{ ControllerType::Switch, { "0d0fc100", "0d0f9200", "6f0e8001", "6f0e8101", "6f0e8401", "6f0e8501", "6f0e8701", "6f0e8801", "0d0faa00", "d62011a7", "d62012a7", "d62013a7", "d62014a7", "d62015a7", "d62016a7" } },
					{ ControllerType::SwitchJoyConLeft, { "7e050620" } },
					{ ControllerType::SwitchJoyConRight, { "7e050720" } },
					{ ControllerType::SwitchLike, { "6e050720", "6e050820", "9b282b00", "9b282c00", "79000018", "57696f74", "7e051720", "2509e803", "7e053003", "7e050820", "ec11e1a7", "791d0103" } },
					{ ControllerType::SwitchPro, { "7e050920", "0d0ff600", "0d0fdc00", "6f0e8601" } },
					{ ControllerType::WiiRemote, { "79000318" } },
					{ ControllerType::XBox360, { "7900d418", "eb0302ff", "4f0426b3", "5e048e02", "5e048f02", "5e049102", "5e04a002", "5e04a102", "5e04a902", "5e041907", "6d041dc2", "6d041ec2", "6d041fc2", "6d0442c2", "6e050420", "a3061af5", "38071647", "38071847", "38072647", "38072847", "38073647", "38073847", "38074047", "380726b7", "3807efbe", "380702cb", "380703cb", "380738f7", "55091072", "550900b4", "6f0e0501", "6f0e1301", "6f0e1f01", "6f0e2501", "6f0e2701", "6f0e3101", "6f0e3301", "6f0e4301", "6f0e4701", "6f0e0102", "6f0e1302", "6f0e1f02", "6f0e0103", "6f0e1303", "6f0e1403", "6f0e0104", "6f0e1304", "6f0e0105", "6f0e00f9", "0d0f0a00", "0d0f0c00", "0d0f0d00", "0d0f1600", "0d0f1b00", "0d0f8c00", "0d0fdb00", "38103014", "38103114", "381060b3", "c911f055", "ab120400", "ab120103", "ab120303", "3014a002", "30144847", "301401f8", "6b140106", "32153700", "e415003f", "e4150a3f", "e415103f", "2e16efbe", "891600fd", "891601fd", "891600fe", "49191a04", "ad1b0200", "ad1b0300", "ad1b16f0", "ad1b18f0", "ad1b19f0", "ad1b21f0", "ad1b23f0", "ad1b25f0", "ad1b27f0", "ad1b28f0", "ad1b2ef0", "ad1b36f0", "ad1b38f0", "ad1b39f0", "ad1b3af0", "ad1b3df0", "ad1b3ef0", "ad1b3ff0", "ad1b42f0", "ad1b80f0", "ad1b01f5", "ad1b02f5", "ad1b03f5", "ad1b04f5", "ad1b05f5", "ad1b06f5", "ad1b00f9", "ad1b01f9", "ad1b02f9", "ad1b03f9", "ad1b04f9", "ad1b06f9", "ad1b01fa", "ad1b00fd", "ad1b01fd", "c6240050", "c6240053", "c6240353", "c6240a53", "c6241a53", "c6249753", "c6240055", "c6240155", "c6240255", "c6240355", "c6240655", "c6240d55", "c6240e55", "c6240855", "c6241055", "c624005b", "c624025b", "c624035b", "c624045d", "c624fafa", "c624fbfa", "c624fcfa", "c624fdfa", "c624fefa", "00000000", "5e04a202", "6f0e1414", "6f0e5901", "c624fffa", "0d0f6d00", "0d0fa400", "79003218", "79007f18", "79008318", "eb0301ff", "222c0323", "120cf80e", "6d040010", "45130660", "6e051220", "6b140206", "0d0fae00", "6d040104", "6d040103", "6d04a3ca", "6d0461c2", "6d049102", "7900d318", "0d0fb100", "01000100", "79008e18", "79007c18", "79009c18", "79007418", "ac056b05", "bc205656", "79003018", "a30618f5", "38072045", "38076252", "38076352", "38076652", "c410c082", "d81401a0", "d814cecf", "d814cefa", "242f3900", "6e050320", "300f1101", "d602e589", "38072644", "55090372", "55091472", "450c2043", "45130830", "6b1401a1", "32150009", "341a0104", "341a0108", "341a0608", "341a0908", "d620ad0d", "d6207162", "d620e589", "f827bf0b", "242f00b7", "3136860c", "58622033", "58622047", "78696e70", "79004f18", "b4041024", "0d0f1110", "c3110791", "32150507", "32150707", "49190304", "c6242a89", "c6242b89", "17274431", "c0110055", "c0110591", "c1110191", "c2110791", "fa190706", "15200182", "bc206412", "efbeedfe", "49190204", "79000200" } },
					{ ControllerType::XBoxLike, { "50320210", "b4041124", "b4041224", "791d0900", "c6111000", "bc205250", "4f0428b3", "6d0416c2", "6d0418c2", "6d0419c2", "a0053232", "78230810", "78230a10", "300f0211", "11011714", "11012014", "2a061024", "38101814", "38102014", "11011914", "11013114", "ac052c02", "ac052d02", "ac053d03", "ac055b05", "ac054d04", "55851b06", "d118402c", "050b0045", "5c0a0285", "69646964", "80100900", "c82d11ab", "00800210", "c82d0310", "c82d8010", "351211ab", "c82d12ab", "6b14010c", "85320706" } },
					{ ControllerType::XBoxOne, { "5e04d102", "5e04dd02", "5e04e002", "5e04e302", "5e04ea02", "5e04fd02", "5e04ff02", "5e04000b", "5e04020b", "5e04050b", "5e040a0b", "5e040c0b", "5e04120b", "5e04130b", "5e04200b", "5e04210b", "5e04220b", "3807014a", "6f0e3901", "6f0e3b01", "6f0e3a01", "6f0e4501", "6f0e4601", "6f0e5b01", "6f0e5c01", "6f0e5d01", "6f0e5f01", "6f0e6001", "6f0e6101", "6f0e6201", "6f0e6301", "6f0e6401", "6f0e6501", "6f0e6601", "6f0e6701", "6f0e0502", "6f0e0602", "6f0e4602", "6f0e6102", "6f0e6202", "6f0ea002", "6f0ea102", "6f0ea202", "6f0ea302", "6f0ea402", "6f0ea502", "6f0ea602", "6f0ea702", "6f0ea802", "6f0ea902", "6f0eaa02", "6f0eab02", "6f0eac02", "6f0ead02", "6f0eae02", "6f0eaf02", "6f0eb002", "6f0eb102", "6f0eb302", "6f0eb502", "6f0eb602", "6f0ebd02", "6f0ebe02", "6f0ebf02", "6f0ec002", "6f0ec102", "6f0ec202", "6f0ec302", "6f0ec402", "6f0ec502", "6f0ec602", "6f0ec702", "6f0ec802", "6f0ec902", "6f0eca02", "6f0ecb02", "6f0ecd02", "6f0ece02", "6f0ecf02", "6f0ed502", "6f0e4603", "6f0e4604", "6f0eda02", "6f0ed602", "6f0ed902", "0d0f6300", "0d0f6700", "0d0f7800", "0d0fc500", "3215000a", "3215030a", "3215140a", "3215150a", "d6200120", "d6200220", "d6200320", "d6200420", "d6200520", "d6200620", "d6200920", "d6200a20", "d6200b20", "d6200c20", "d6200d20", "d6200e20", "d6200f20", "d6201120", "d6201220", "d6201520", "d6201620", "d6201720", "d6201820", "d6201920", "d6201a20", "d6200140", "d6200240", "c6241a54", "c6242a54", "c6243a54", "c6241a55", "c6241a56", "c6241a58", "c6241a59", "c6242a59", "c6241a79", "242e5206", "242e1816", "242e8816", "6b141106", "242f5000", "242f2e00", "86982400", "242f9100", "30141907", "0d0fed00", "0d0fc000", "6f0e5201", "6d040710", "6f0eb802", "222c0325", "7900a118", "00008666", "ff111105", "ab120403", "30149102", "3014a902", "30140b07", "6b140406", "6b140506", "6b140606", "6b140906", "ad1b8e02", "ad1ba002", "ad1b0055", "ab20ef55", "c6240955", "16256900", "b1256003", "222c0322", "242f1100", "242f5300", "242fb700", "6d040000", "6d040410", "6d040810", "6d0401f3", "3807a002", "38076372", "380738b7", "380729cb", "380701f4", "7900c218", "7900c818", "7900cf18", "120c170e", "120c1c0e", "120c220e", "120c300e", "d2d2d2d2", "620d1a9a", "620d1b9a", "000e000e", "6f0e2a01", "6f0eb202", "0d0f9700", "0d0fba00", "0d0fd800", "ff0fa102", "5e046708", "d0163f0f", "242f8f00", "6f0e01f5", "3215290a", "6f0ed702", "0d0f5001", "5e04030b", "d6200228", "15194000" } }
				};
		};
	}

}