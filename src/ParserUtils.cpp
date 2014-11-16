#include "../include/ParserUtils.hpp"

const std::string ParserUtils::base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                              "abcdefghijklmnopqrstuvwxyz"
                                              "0123456789+/";

bool ParserUtils::base64_encode(std::string& data)
{
    int count = 0;
    unsigned char input_bytes[3] = { '\0', '\0', '\0' };
    unsigned char byte_array[4];
    std::string result;

    for (unsigned int i = 0; i < data.size(); ++i)
    {
        input_bytes[count++] = data[i];
        if (count == 3 || (i == data.size() - 1))
        {
            byte_array[0] = input_bytes[0] >> 2;
            byte_array[1] = ((input_bytes[0] & 0x3) << 4) | (input_bytes[1] >> 4);
            byte_array[2] = ((input_bytes[1] & 0xf) << 2) | (input_bytes[2] >> 6);
            byte_array[3] = input_bytes[2] & 0x3f;

            memset(input_bytes, '\0', 3);

            for (int j = 0; j < count + 1; j++)
                result += base64_table[byte_array[j]];

            if (count != 3)
                for (int i = count; i < 3; ++i)
                    result += '=';
            else
                count = 0;
        }
    }

    data = result;
    return true;
}

bool ParserUtils::base64_decode(std::string& data)
{
    int count = 0;
    unsigned char input_bytes[4] = { '\0', '\0', '\0', '\0' };
    unsigned char byte_array[3];
    std::string result;

    for (unsigned int i = 0; i < data.size(); ++i)
    {
        if (is_valid_base64(data[i]))
            input_bytes[count++] = base64_table.find(data[i]);
        if (count == 4 || data[i] == '=')
        {
            byte_array[0] = (input_bytes[0] << 2) | ((input_bytes[1] & 0x30) >> 4);
            byte_array[1] = ((input_bytes[1] & 0xf) << 4) | ((input_bytes[2] & 0x3c) >> 2);
            byte_array[2] = ((input_bytes[2] & 0x3) << 6) | input_bytes[3];

            memset(input_bytes, '\0', 4);

            for (int j = 0; j < count - 1; j++)
                result += byte_array[j];

            if (count != 4)
                break;
            else
                count = 0;
        }
    }

    data = result;
    return true;
}

bool ParserUtils::decompressString(std::string& data)
{
    z_stream zstream;

    std::string outstring;

    zstream.zalloc = Z_NULL;
    zstream.zfree = Z_NULL;
    zstream.opaque = Z_NULL;
    zstream.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(data.data()));
    zstream.avail_in = data.size();

    int result;
    result = inflateInit2(&zstream, 15 + 32);

	char outbuffer[32768];

    if (result != Z_OK)
    {
        return false;
    }

    do
    {
        zstream.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zstream.avail_out = sizeof(outbuffer);

        result = inflate(&zstream, Z_SYNC_FLUSH);

        switch (result)
        {
            case Z_NEED_DICT:
            case Z_STREAM_ERROR:
                result = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&zstream);
                return false;
        }

        if (outstring.size() < zstream.total_out)
        {
            outstring.append(outbuffer, zstream.total_out - outstring.size());
        }
    } while (result != Z_STREAM_END);

    if (zstream.avail_in != 0)
    {
        return false;
    }

    inflateEnd(&zstream);

    data = outstring;

    return true;
}
