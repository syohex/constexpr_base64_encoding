#include <iostream>
#include <cstddef>
#include <utility>

namespace {

template <size_t N>
struct Base64Encode {
    template <size_t... Nums>
    constexpr Base64Encode(const char (&input)[N], std::integer_sequence<size_t, Nums...>) : data{0} {
        constexpr char ENCODE_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        size_t i = 0, j = 0;
        for (; i < N - 1; i += 3, j += 4) {
            std::uint32_t v = input[i];
            v = i + 1 < N - 1 ? ((v << 8) | input[i + 1]) : v << 8;
            v = i + 2 < N - 1 ? ((v << 8) | input[i + 2]) : v << 8;

            data[j] = ENCODE_TABLE[(v >> 18) & 0x3f];
            data[j + 1] = ENCODE_TABLE[(v >> 12) & 0x3f];
            if (i + 1 < N - 1) {
                data[j + 2] = ENCODE_TABLE[(v >> 6) & 0x3f];
            } else {
                data[j + 2] = '=';
            }
            if (i + 2 < N - 1) {
                data[j + 3] = ENCODE_TABLE[v & 0x3f];
            } else {
                data[j + 3] = '=';
            }
        }

        data[j] = '\0';
    }

    char data[2 * N];
};

template <size_t N>
constexpr Base64Encode<N> ToBase64(const char (&input)[N]) {
    return Base64Encode<N>(input, std::make_integer_sequence<size_t, N>{});
}

} // namespace

int main() {
    constexpr auto base64 = ToBase64("Hello");
    static_assert(base64.data[0] == 'S');
    static_assert(base64.data[1] == 'G');
    static_assert(base64.data[2] == 'V');
    static_assert(base64.data[3] == 's');
    static_assert(base64.data[4] == 'b');
    static_assert(base64.data[5] == 'G');
    static_assert(base64.data[6] == '8');
    static_assert(base64.data[7] == '=');

    std::cout << base64.data << std::endl;
    return 0;
}