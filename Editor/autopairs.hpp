#ifndef AUTOPAIRS_HPP
#define AUTOPAIRS_HPP


namespace AutoPairs
{
    inline char get_closing_pair(char open_char)
    {
        switch (open_char)
        {
            case '(':
                return ')';
            case '{':
                return '}';
            case '[':
                return ']';
            case '"':
                return '"';
            case '\'':
                return '\'';
            default: return '\0';
        }
    }
}

#endif
