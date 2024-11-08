#include <utility>

inline auto get_rdi_msg()
{
  static constexpr std::uint8_t res[] =
    {
                  0xc0, 0xc7, 0xab, 0x84, 0x00, 0x6f,
      0xdf, 0x93, 0x88, 0x16, 0x98, 0x18, 0xfe, 0xdb,
      0x88, 0xd8, 0x9b, 0xc0, 0xf8, 0x7b, 0xb7, 0xfb,
      0x48, 0xa6, 0x01, 0x14, 0x17, 0xc5, 0x83, 0xc0,
      0x80, 0x35, 0x30, 0x30, 0x31, 0x34, 0x39, 0x39,
      0x34, 0xb6, 0xcd, 0xc0, 0x89, 0x58, 0x46, 0x30,
      0x30, 0x30, 0x30, 0x30, 0x4c, 0x43, 0x57, 0x56,
      0xb3, 0xb4, 0x80, 0x80, 0x81, 0x4f, 0x53, 0x4d,
      0x49, 0x20, 0x53, 0x49, 0x20, 0x32, 0x30, 0x32,
      0x32, 0x31, 0x32, 0x31, 0x35, 0x20, 0x43, 0x53,
      0x20, 0x45, 0x55, 0x20, 0x50, 0x20, 0x31, 0x32,
      0x32, 0x35, 0x30, 0x20, 0xb0, 0x80, 0xe0, 0x4f,
      0x50, 0x45, 0x4d, 0x43, 0xd3, 0x62, 0x57, 0xda,
      0x09, 0x52, 0x1a, 0xa0, 0x0c, 0x2b, 0xe5, 0x85,
      0x82, 0x09, 0xc9, 0x81, 0x81, 0x81, 0x81, 0x82,
      0x09, 0xc9, 0x82, 0x81, 0x81, 0xff, 0x01, 0x08,
      0x8a, 0x80, 0x86, 0xe0, 0x96, 0xce, 0xe0, 0x86,
      0x58, 0x45, 0x55, 0xd2, 0xe0, 0x8c, 0xce, 0xe0,
      0x8d, 0xd9, 0xc0, 0x8f, 0x83, 0xa0, 0x09, 0x52,
      0x1a, 0x9e, 0xe0, 0x84, 0x09, 0x52, 0x1a, 0x9f,
      0x82, 0xff, 0x81, 0x81, 0x81, 0x09, 0x52, 0x1a,
      0xa0, 0x0c, 0x2b, 0xe5, 0x4a, 0xc0, 0x01, 0xc9,
      0x82, 0x80, 0xc0, 0xb1, 0x81, 0x37, 0xf0, 0x83,
      0xc0, 0x8c, 0x35, 0x30, 0x30, 0x31, 0x35, 0x35,
      0x39, 0x31, 0xb7, 0xcd, 0xc0, 0x89, 0x58, 0x46,
      0x30, 0x30, 0x30, 0x30, 0x30, 0x4c, 0x4a, 0x44,
      0x58, 0xb4, 0xb4, 0x8a, 0x43, 0x20, 0x31, 0x32,
      0x33, 0x30, 0x30, 0x20, 0xb0, 0xe0, 0x4f, 0x43,
      0x45, 0x4d, 0x43, 0xd3, 0x00, 0x49, 0x82, 0x83,
      0x00, 0xfb, 0x82, 0x83, 0x00, 0xfb, 0x80, 0x80,
      0x86, 0xe0, 0x96, 0xce, 0xe0, 0x86, 0x58, 0x45,
      0x55, 0xd2, 0xe0, 0x8c, 0xce, 0xe0, 0x8d, 0xd9,
      0xc0, 0x8f, 0x83, 0xa0, 0x09, 0x52, 0x1a, 0x9e,
      0xe0, 0x84, 0x09, 0x52, 0x1a, 0x9f, 0x02, 0xc0,
      0x80, 0x80, 0x81, 0xfe, 0x83, 0xc0, 0x8c, 0x35,
      0x30, 0x30, 0x31, 0x35, 0x35, 0x39, 0x31, 0xb8,
      0xcd, 0xc0, 0x89, 0x58, 0x46, 0x30, 0x30, 0x30,
      0x30, 0x30, 0x4c, 0x4a, 0x44, 0x59, 0xb2, 0xb4,
      0x8a, 0x50, 0x20, 0x31, 0x32, 0x33, 0x30, 0x30,
      0x20, 0xb0, 0xe0, 0x4f, 0x50, 0x45, 0x4d, 0x43,
      0xd3, 0x80, 0x80, 0x86, 0xe0, 0x96, 0xce, 0xe0,
      0x86, 0x58, 0x45, 0x55, 0xd2, 0xe0, 0x8c, 0xce,
      0xe0, 0x8d, 0xd9, 0xc0, 0x8f, 0x83, 0xa0, 0x09,
      0x52, 0x1a, 0x9e, 0xe0, 0x84, 0x09, 0x52, 0x1a,
      0x9f, 0x02, 0xc0, 0x80, 0x80, 0x01, 0x83, 0x7a,
      0x07, 0xcf, 0x83, 0xc0, 0xf4, 0x31, 0x33, 0x30,
      0x35, 0x31, 0x31, 0xb5, 0xcd, 0xc0, 0x88, 0x58,
      0x46, 0x30, 0x30, 0x30, 0x30, 0x30, 0x4a, 0x32,
      0x55, 0x55, 0xb8, 0xb4, 0x96, 0x33, 0x30, 0x36,
      0x31, 0x35, 0x20, 0x43, 0x53, 0x20, 0x45, 0x55,
      0x20, 0x43, 0x20, 0x39, 0x34, 0x35, 0x30, 0x20,
      0xb0, 0xe0, 0x4f, 0x43, 0x45, 0x4d, 0x43, 0xd3,
      0x60, 0x49, 0x82, 0x09, 0x52, 0x63, 0xd8, 0x0c,
      0x2c, 0xc3, 0x82, 0x07, 0xb1, 0x82, 0x82, 0x07,
      0xb1, 0xff, 0x02, 0x19, 0xdd, 0x80, 0x86, 0xe0,
      0x96, 0xce, 0xe0, 0x86, 0x58, 0x45, 0x55, 0xd2,
      0xe0, 0x8c, 0xce, 0xe0, 0x8d, 0xd9, 0xc0, 0x8f,
      0x83, 0xa0, 0x09, 0x52, 0x63, 0xd6, 0xe0, 0x84,
      0x09, 0x52, 0x63, 0xd7, 0x09, 0x52, 0x63, 0xd8,
      0x0c, 0x2c, 0xc3, 0x02, 0xc0, 0x80, 0x80, 0x81,
      0x81, 0x83, 0xc0, 0x8c, 0x31, 0x33, 0x30, 0x35,
      0x31, 0x31, 0x35, 0xb3, 0xcd, 0xc0, 0x88, 0x58,
      0x46, 0x30, 0x30, 0x30, 0x30, 0x30, 0x4a, 0x32,
      0x55, 0x56, 0xb6, 0xb4, 0x89, 0x50, 0x20, 0x39,
      0x34, 0x35, 0x30, 0x20, 0xb0, 0xe0, 0x4f, 0x50,
      0x45, 0x4d, 0x43, 0xd3, 0x00, 0x00, 0x82, 0xff,
      0x00, 0x47, 0x83, 0x80, 0x86, 0xe0, 0x96, 0xce,
      0xe0, 0x86, 0x58, 0x45, 0x55, 0xd2, 0xe0, 0x8c,
      0xce, 0xe0, 0x8d, 0xd9, 0xc0, 0x8f, 0x83, 0xa0,
      0x09, 0x52, 0x63, 0xd6, 0xe0, 0x84, 0x09, 0x52,
      0x63, 0xd7, 0x02, 0xc0, 0x80, 0x80, 0x81, 0x81,
      0x83, 0xc0, 0x8c, 0x31, 0x33, 0x30, 0x35, 0x31,
      0x31, 0x35, 0xb4, 0xcd, 0xc0, 0xf8, 0x58, 0x46,
      0x30, 0x30, 0x30, 0x30, 0x30, 0x4a, 0x32, 0x55,
      0xd7, 0xb4, 0x89, 0x43, 0x20, 0x39, 0x35, 0x30,
      0x30, 0x20, 0xb0, 0xe0, 0x4f, 0x43, 0x45, 0x4d,
      0x43, 0xd3, 0x00, 0x49, 0x82, 0x83, 0x00, 0xdf,
      0x82, 0x83, 0x00, 0xdf, 0xff, 0x02, 0x16, 0xfb,
      0x80, 0x86, 0xe0, 0x96, 0xce, 0xe0, 0x86, 0x58,
      0x45, 0x55, 0xd2, 0xe0, 0x8c, 0xce, 0xe0, 0x8d,
      0xd9, 0xc0, 0x8f, 0x83, 0xa0, 0x09, 0x52, 0x63,
      0xd6, 0xe0, 0x84, 0x09, 0x52, 0x63, 0xd7, 0x02,
      0xc0, 0x80, 0x80, 0x81, 0x81, 0x83, 0xc0, 0x8c,
      0x31, 0x33, 0x30, 0x35, 0x31, 0x31, 0x35, 0xb5,
      0xcd, 0xc0, 0x88, 0x58, 0x46, 0x30, 0x30, 0x30,
      0x30, 0x30, 0x4a, 0x32, 0x55, 0x58, 0xb2, 0xb4,
      0x89, 0x50, 0x20, 0x39, 0x35, 0x30, 0x30, 0x20,
      0xb0, 0xe0, 0x4f, 0x50, 0x45, 0x4d, 0x43, 0xd3,
      0x00, 0x00, 0x82, 0xff, 0x00, 0x48, 0x95, 0x80,
      0x86, 0xe0, 0x96, 0xce, 0xe0, 0x86, 0x58, 0x45,
      0x55, 0xd2, 0xe0, 0x8c, 0xce, 0xe0, 0x8d, 0xd9,
      0xc0, 0x8f, 0x83, 0xa0, 0x09, 0x52, 0x63, 0xd6,
      0xe0, 0x84, 0x09, 0x52, 0x63, 0xd7, 0x02, 0xc0,
      0x80, 0x80, 0x81, 0x81, 0x83, 0xc0, 0x8c, 0x31,
      0x33, 0x30, 0x35, 0x31, 0x31, 0x35, 0xb6, 0xcd,
      0xc0, 0x88, 0x58, 0x46, 0x30, 0x30, 0x30, 0x30,
      0x30, 0x4a, 0x32, 0x55, 0x59, 0xb0, 0xb4, 0x89,
      0x43, 0x20, 0x39, 0x35, 0x35, 0x30, 0x20, 0xb0,
      0xe0, 0x4f, 0x43, 0x45, 0x4d, 0x43, 0xd3, 0x00,
      0x49, 0x82, 0x82, 0x07, 0xbb, 0x82, 0x82, 0x07,
      0xbb, 0xff, 0x02, 0x14, 0x9b, 0x80, 0x86, 0xe0,
      0x96, 0xce, 0xe0, 0x86, 0x58, 0x45, 0x55, 0xd2,
      0xe0, 0x8c, 0xce, 0xe0, 0x8d, 0xd9, 0xc0, 0x8f,
      0x83, 0xa0, 0x09, 0x52, 0x63, 0xd6, 0xe0, 0x84,
      0x09, 0x52, 0x63, 0xd7, 0x02, 0xc0, 0x80, 0x80,
      0x81, 0x81, 0x83, 0xc0, 0x8c, 0x31, 0x33, 0x30,
      0x35, 0x31, 0x31, 0x35, 0xb7, 0xcd, 0xc0, 0xf8,
      0x58, 0x46, 0x30, 0x30, 0x30, 0x30, 0x30, 0x4a,
      0x32, 0x55, 0xda, 0xb4, 0x89, 0x50, 0x20, 0x39,
      0x35, 0x35, 0x30, 0x20, 0xb0, 0xe0, 0x4f, 0x50,
      0x45, 0x4d, 0x43, 0xd3, 0x00, 0x00, 0x82, 0xff,
      0x00, 0x49, 0xa9, 0x80, 0x86, 0xe0, 0x96, 0xce,
      0xe0, 0x86, 0x58, 0x45, 0x55, 0xd2, 0xe0, 0x8c,
      0xce, 0xe0, 0x8d, 0xd9, 0xc0, 0x8f, 0x83, 0xa0,
      0x09, 0x52, 0x63, 0xd6, 0xe0, 0x84, 0x09, 0x52,
      0x63, 0xd7, 0x02, 0xc0, 0x80, 0x80, 0x81, 0x81,
      0x83, 0xc0, 0x8c, 0x31, 0x33, 0x30, 0x35, 0x31,
      0x31, 0x35, 0xb8, 0xcd, 0xc0, 0x88, 0x58, 0x46,
      0x30, 0x30, 0x30, 0x30, 0x30, 0x4a, 0x32, 0x56,
      0x30, 0xb5, 0xb4, 0x89, 0x43, 0x20, 0x39, 0x36,
      0x30, 0x30, 0x20, 0xb0, 0xe0, 0x4f, 0x43, 0x45,
      0x4d, 0x43, 0xd3, 0x00, 0x49, 0x82, 0x83, 0x00,
      0xe0, 0x82, 0x83, 0x00, 0xe0, 0xff, 0x02, 0x11,
      0xbc, 0x80, 0x86, 0xe0, 0x96, 0xce, 0xe0, 0x86,
      0x58, 0x45, 0x55, 0xd2, 0xe0, 0x8c, 0xce, 0xe0,
      0x8d, 0xd9, 0xc0, 0x8f, 0x83, 0xa0, 0x09, 0x52,
      0x63, 0xd6, 0xe0, 0x84, 0x09, 0x52, 0x63, 0xd7,
      0x02, 0xc0, 0x80, 0x80, 0x81, 0x81, 0x83, 0xc0,
      0x8c, 0x31, 0x33, 0x30, 0x35, 0x31, 0x31, 0x35,
      0xb9, 0xcd, 0xc0, 0x88, 0x58, 0x46, 0x30, 0x30,
      0x30, 0x30, 0x30, 0x4a, 0x32, 0x56, 0x31, 0xb3,
      0xb4, 0x89, 0x50, 0x20, 0x39, 0x36, 0x30, 0x30,
      0x20, 0xb0, 0xe0, 0x4f, 0x50, 0x45, 0x4d, 0x43,
      0xd3, 0x00, 0x00, 0x82, 0xff, 0x00, 0x4a, 0xbe,
      0x80, 0x86, 0xe0, 0x96, 0xce, 0xe0, 0x86, 0x58,
      0x45, 0x55, 0xd2, 0xe0, 0x8c, 0xce, 0xe0, 0x8d,
      0xd9, 0xc0, 0x8f, 0x83, 0xa0, 0x09, 0x52, 0x63,
      0xd6, 0xe0, 0x84, 0x09, 0x52, 0x63, 0xd7, 0x02,
      0xc0, 0x80, 0x80, 0x81, 0x81, 0x83, 0xc0, 0x8c,
      0x31, 0x33, 0x30, 0x35, 0x31, 0x31, 0x36, 0xb0,
      0xcd, 0xc0, 0x88, 0x58, 0x46, 0x30, 0x30, 0x30,
      0x30, 0x30, 0x4a, 0x32, 0x56, 0x32, 0xb1, 0xb4,
      0x89, 0x43, 0x20, 0x39, 0x36, 0x35, 0x30, 0x20,
      0xb0, 0xe0, 0x4f, 0x43, 0x45, 0x4d, 0x43, 0xd3,
      0x00, 0x49, 0x82, 0x82, 0x07, 0xc5, 0x82, 0x82,
      0x07, 0xc5, 0xff, 0x02, 0x0e, 0xe0, 0x80, 0x86,
      0xe0, 0x96, 0xce, 0xe0, 0x86, 0x58, 0x45, 0x55,
      0xd2, 0xe0, 0x8c, 0xce, 0xe0, 0x8d, 0xd9, 0xc0,
      0x8f, 0x83, 0xa0, 0x09, 0x52, 0x63, 0xd6, 0xe0,
      0x84, 0x09, 0x52, 0x63, 0xd7, 0x02, 0xc0, 0x80,
      0x80, 0x81, 0x81, 0x83, 0xc0, 0xf4, 0x31, 0x33,
      0x30, 0x35, 0x31, 0x31, 0xb6, 0xcd, 0xc0, 0x88,
      0x58, 0x46, 0x30, 0x30, 0x30, 0x30, 0x30, 0x4a,
      0x32, 0x56, 0x33, 0xb9, 0xb4, 0x89, 0x50, 0x20,
      0x39, 0x36, 0x35, 0x30, 0x20, 0xb0, 0xe0, 0x4f,
      0x50, 0x45, 0x4d, 0x43, 0xd3, 0x00, 0x00, 0x82,
      0xff, 0x00, 0x4b, 0xd6, 0x80, 0x86, 0xe0, 0x96,
      0xce, 0xe0, 0x86, 0x58, 0x45, 0x55, 0xd2, 0xe0,
      0x8c, 0xce, 0xe0, 0x8d, 0xd9, 0xc0, 0x8f, 0x83,
      0xa0, 0x09, 0x52, 0x63, 0xd6, 0xe0, 0x84, 0x09,
      0x52, 0x63, 0xd7, 0x02, 0xc0, 0x80, 0x80
    };
  auto char_res = reinterpret_cast<const char*>(res);
  return std::make_pair(char_res, char_res + sizeof(res));
}
