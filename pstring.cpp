#include "pstring.h"

namespace Plib {
    const unsigned Pstring::Ascend = 0;
    const unsigned Pstring::Descend = 1;
    const unsigned Pstring::AlphaC = 10;
    const unsigned Pstring::AlphaS = 100;
    const unsigned Pstring::Num = 1000;

    Pstring::Pstring() :
            isAlloc(false), tmp(0) {
        str = "";
    }

    Pstring::~Pstring() {
        if (isAlloc)
            delete[] tmp;
    }

    Pstring::Pstring(std::string st) :
            isAlloc(false) {
        assign(st);
    }

    Pstring::Pstring(const char *st) :
            isAlloc(false) {
        assign(st);
    }

    void Pstring::allocTemp(size_t sz) {
        isAlloc = true;
        tmp = new char[sz];
    }

    void Pstring::deallocTemp() {
        isAlloc = false;
        delete[] tmp;
    }

    void Pstring::sync() {
        str = tmp;
    }

    void Pstring::assign(const char *st) {
        str = st;
    }

    void Pstring::assign(Pstring st) {
        str = st.str;
    }

    void Pstring::assign(std::string st) {
        str = st;
    }

    Pstring Pstring::append(const char *st) {
        str.append(st);
        return import(str);
    }

    Pstring Pstring::append(Pstring st) {
        str.append(st.str);
        return import(str);
    }

    Pstring Pstring::append(std::string st) {
        str.append(st);
        return import(str);
    }

    void Pstring::write(long long len) {
        if (!len)
            std::cout.write(str.c_str(), str.length());
        else
            std::cout.write(str.c_str(), len);
    }

    void Pstring::read() {
        getline(std::cin, str);
    }

    std::ostream &operator<<(std::ostream &os, Pstring st) {
        return os << st.str;
    }

    std::istream &operator>>(std::istream &is, Pstring &st) {
        return is >> st.str;
    }

    size_t Pstring::size() {
        return str.length();
    }

    void Pstring::assignTo(Pstring &st) {
        st = this->str;
    }

    void Pstring::appendTo(Pstring &st) {
        st.append(str);
    }

    Pstring Pstring::slice(size_t a, size_t b) {
        Pstring tmp;
        tmp.assign(str.substr(a, b - a + 1));
        return tmp;
    }


    bool Pstring::operator!=(Pstring tmp) {
        if (str == tmp.str)
            return false;
        return true;
    }

    bool Pstring::operator==(Pstring tmp) {
        if (str == tmp.str)
            return true;
        return false;
    }


    bool Pstring::operator>=(Pstring tmp) {
        if (str >= tmp.str)
            return true;
        return false;
    }

    bool Pstring::operator<=(Pstring tmp) {
        if (str <= tmp.str)
            return true;
        return false;
    }

    bool Pstring::operator>(Pstring tmp) {
        if (str > tmp.str)
            return true;
        return false;
    }

    bool Pstring::operator<(Pstring tmp) {
        if (str < tmp.str)
            return true;
        return false;
    }

    void Pstring::operator=(const char *st) {
        assign(st);
    }

    void Pstring::operator=(Pstring st) {
        assign(st);
    }

    void Pstring::operator=(std::string st) {
        assign(st);
    }

    bool Pstring::contain(Pstring st) {
        Pstring tmp;
        long long i = 0;
        while (i + st.size() <= size()) {
            tmp = slice(i, i + st.size() - 1);
            if (tmp == st)
                return true;
            i++;
        }
        return false;
    }

    long long Pstring::find(Pstring st) {
        Pstring tmp;
        long long i = 0;
        while (i + st.size() <= size()) {
            tmp = slice(i, i + st.size() - 1);
            if (tmp == st)
                return i;
            i++;
        }
        return -1;
    }


    long long Pstring::findLast(Pstring st) {
        Pstring tmp;
        st.reverse();
        Pstring rev = str;
        rev.reverse();
        long long i = 0;
        while (i + st.size() <= rev.size()) {
            tmp = rev.slice(i, i + st.size() - 1);
            if (tmp == st)
                return size()-(i+st.size());
            i++;
        }
        return -1;
    }


    Pstring Pstring::caseUp() {
        for (long long i = 0; i < size(); i++)
            if (islower(str[i]))
                str[i] = toupper(str[i]);
        return import(str);
    }

    Pstring Pstring::caseDown() {
        for (long long i = 0; i < size(); i++)
            if (isupper(str[i]))
                str[i] = tolower(str[i]);
        return import(str);
    }

    Pstring Pstring::caseTitle() {
        str[0] = toupper(str[0]);
        for (unsigned long i = 0; i < size(); i++) {
            if (str[i] == ' ' || str[i] == '\t' || str[i] == '.')
                str[i + 1] = toupper(str[i + 1]);
            else
                str[i + 1] = tolower(str[i + 1]);
        }
        return import(str);
    }

    size_t Pstring::findAll(std::vector<size_t> &count, Pstring st) {
        Pstring tmp;
        long long i = 0;
        while (i + st.size() <= size()) {
            tmp = slice(i, i + st.size() - 1);
            if (tmp == st)
                count.push_back(i);
            i++;
        }
        return count.size();
    }

    Pstring Pstring::replace(Pstring from, Pstring to) {
        std::vector<size_t> val;
        size_t i, k, j, l = 0, len = findAll(val, from);
        Pstring tmp;
        tmp = str;
        if(len == 0)    {
            return str;
        }
        l = 0;
        j = 0;
        str.resize(tmp.size() - (len * from.size()) + (len * to.size()));
        str.empty();
        for (i = 0; i < tmp.size(); i++) {
            if (i == val[j]) {
                for (k = 0; k < to.size(); k++) {
                    str[l] = to.str[k];
                    l++;
                }
                j++;
                i += from.size() - 1;
            } else {
                str[l] = tmp.str[i];
                l++;
            }
        }
        return Pstring::import(str);
    }

    Pstring Pstring::replace(size_t pos1, size_t pos2, Pstring to) {
        Pstring from;
        from = slice(pos1, pos2);
        long long i, k, j, l = 0;
        Pstring tmp;
        tmp = str;
        str.empty();
        str.resize(tmp.size() - (from.size()) + (to.size()));
        l = 0;
        j = 0;
        for (i = 0; i < tmp.size(); i++) {
            if (i == pos1) {
                for (k = 0; k < to.size(); k++) {
                    str[l] = to.str[k];
                    l++;
                }
                j++;
                i += from.size() - 1;
            } else {
                str[l] = tmp.str[i];
                l++;
            }
        }
        return import(str);
    }

    char *Pstring::getCString() {
        return (char *) str.c_str();
    }

    std::string Pstring::getStdString() {
        return str;
    }

    long long Pstring::findExcept(Pstring st) {
        Pstring tmp;
        size_t i = 0;
        while (i + st.size() <= size()) {
            tmp = slice(i, i + st.size() - 1);
            if (tmp == st)
                i = i + st.size() - 1;
            if (tmp != st)
                return i;
            i++;
        }
        return -1;
    }

    void Pstring::clear() {
        str.clear();
    }

    bool Pstring::containAfter(size_t pos, Pstring st) {
        size_t s = 0, j = 0, i;
        for (i = pos; i < size(); i++) {
            if (str[i] == st.str[j]) {
                ++j;
                if (j == st.size()) {
                    s = i - j + 1;
                    break;
                } else
                    s = 0;
            } else {
                if (j > 0)
                    i--;
                j = 0;
            }
        }
        if (j == st.size())
            return true;
        else
            return false;
    }

    bool Pstring::containBefore(size_t pos, Pstring st) {
        size_t s = 0, j = 0, i;
        for (i = 0; i <= pos; i++) {
            if (str[i] == st.str[j]) {
                ++j;
                if (j == st.size()) {
                    s = i - j + 1;
                    break;
                } else
                    s = 0;
            } else {
                if (j > 0)
                    i--;
                j = 0;
            }
        }
        if (j == st.size())
            return true;
        else
            return false;
    }


    bool Pstring::containWithin(size_t pos1, size_t pos2, Pstring st) {
        long long s = 0, j = 0, i;
        for (i = ((pos1 > pos2) ? pos2 : pos1); i <= ((pos1 > pos2) ? pos1 : pos2);
             i++) {
            if (str[i] == st.str[j]) {
                ++j;
                if (j == st.size()) {
                    s = i - j + 1;
                    break;
                } else
                    s = 0;
            } else {
                if (j > 0)
                    i--;
                j = 0;
            }
        }
        if (j == st.size())
            return true;
        else
            return false;
    }

    Pstring Pstring::replaceFromPattern(std::vector<size_t> val, size_t from, Pstring to) {
        sort(val, Pstring::Ascend);
        size_t i, k, j, l = 0, len = val.size();
        Pstring tmp;
        tmp = str;
        str.resize(tmp.size() - (len * from) + (len * to.size()));
        l = 0;
        j = 0;
        for (i = 0; i < tmp.size(); i++) {
            if (i == val[j]) {
                for (k = 0; k < to.size(); k++) {
                    str[l] = to.str[k];
                    l++;
                }
                j++;
                i += from - 1;
            } else {
                str[l] = tmp.str[i];
                l++;
            }
        }
        return import(str);
    }

    Pstring Pstring::remove(size_t pos1, size_t pos2) {
        return replace(pos1, pos2, Pstring(""));
    }

    Pstring Pstring::remove(Pstring st) {
        return replace(st, Pstring(""));
    }

    Pstring Pstring::removeFromPattern(std::vector<size_t> v, size_t from) {
        return replaceFromPattern(v, from, Pstring(""));
    }

    void Pstring::swap(Pstring &st) {
        Pstring S;
        assignTo(S);
        assign(st);
        st.assign(S);
    }

    void Pstring::reverse() {
        Pstring tmp;
        tmp = str;
        long long i;
        for (i = 0; i < tmp.size(); i++)
            str[i] = tmp.str[tmp.size() - i - 1];
    }

    Pstring Pstring::operator-() {
        Pstring tmp;
        tmp = str;
        tmp.reverse();
        return tmp;
    }

    Pstring Pstring::insert(size_t pos, Pstring st) {
        if (pos >= size())
            pos = size();
        Pstring tmp;
        if (pos != 0)
            tmp.assign(slice(0, pos - 1));
        tmp.append(st);
        tmp.append(slice(pos, size() - 1));
        assign(tmp);
        return import(str);
    }

    Pstring Pstring::pop(size_t sz) {
        Pstring tmp;
        tmp = slice(size() - sz, size() - 1);
        remove(size() - sz, size() - 1);
        return tmp;
    }


    Pstring Pstring::operator+(Pstring st) {
        Pstring tmp;
        tmp.assign(str);
        tmp.append(st.str);
        return tmp;
    }

    void Pstring::operator+=(Pstring st) {
        append(st.str);
    }


    Pstring Pstring::operator-(Pstring st) {
        Pstring tmp;
        tmp = str;
        tmp.remove(st);
        return tmp;
    }

    void Pstring::operator-=(Pstring st) {
        remove(st);
    }


    Pstring Pstring::operator[](size_t v) {
        return import(str[v]);
    }

    Pstring Pstring::randomString(size_t sz, const int typ) {
        time_t t;
        Pstring st;
        srand((unsigned) time(&t));
        Pstring x;
        int sx;
        for (int i = 0; i < sz; i++)
            switch (typ) {
                case AlphaS:
                    x = "abcdefghijklmnopqrstuvwxyz";
                    sx = x.size();
                    st.append(x[rand() % sx]);
                    break;
                case AlphaC:
                    x = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    sx = x.size();
                    st.append(x[rand() % sx]);
                    break;
                case Num:
                    x = "0123456789";
                    sx = x.size();
                    st.append(x[rand() % sx]);
                    break;
                case AlphaS + AlphaC:
                    x = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUwWxXyYzZ";
                    sx = x.size();
                    st.append(x[rand() % sx]);
                    break;
                case AlphaS + Num:
                    x = "0ab1cd2ef3gh4ij5kl6mn7op8qr9stuvwxyz";
                    sx = x.size();
                    st.append(x[rand() % sx]);
                    break;
                case AlphaC + Num:
                    x = "0AB1CD2EF3GH4IJ5KL6MN7OPQ8RSTUV9WXYZ";
                    sx = x.size();
                    st.append(x[rand() % sx]);
                    break;
                case AlphaS + AlphaC + Num:
                    x = "0aAbB1cCd2DeEf3FgGh4HiIj5JkKlL6mMnN7oOpP8qQrRsSt9TuUwWxXyYzZ";
                    sx = x.size();
                    st.append(x[rand() % sx]);
            }
        return st;
    }

    long long Pstring::toLongLong() {
        long long v;
        std::istringstream is(str);
        is >> v;
        return v;
    }

    int Pstring::toInt() {
        int v;
        std::istringstream is(str);
        is >> v;
        return v;
    }

    size_t Pstring::toSize_t() {
        long long v;
        std::istringstream is(str);
        is >> v;
        return v;
    }

    double Pstring::toDouble() {
        double v;
        std::istringstream is(str);
        is >> v;
        return v;
    }

    char Pstring::toChar() {
        char v;
        std::istringstream is(str);
        is >> v;
        return v;
    }

    Pstring Pstring::import(const char *a) {
        std::ostringstream os;
        os << a;
        std::string tmp = os.str();
        return import(tmp);
    }

    Pstring Pstring::import(long long a) {
        std::ostringstream os;
        os << a;
        std::string tmp = os.str();
        return import(tmp);
    }
    Pstring Pstring::import(size_t a) {
        std::ostringstream os;
        os << a;
        std::string tmp = os.str();
        return import(tmp);
    }

    Pstring Pstring::import(std::string a) {
        Pstring tmp(a);
        return tmp;
    }

    Pstring Pstring::import(int a) {
        std::ostringstream os;
        os << a;
        std::string tmp = os.str();
        return import(tmp);
    }

    Pstring Pstring::import(double a) {
        std::ostringstream os;
        os << a;
        std::string tmp = os.str();
        return import(tmp);
    }

    Pstring Pstring::import(char a) {
        std::ostringstream os;
        os << a;
        std::string tmp = os.str();
        return import(tmp);
    }

    void Pstring::sort(std::vector<size_t> &v, int l) {
        size_t i, j, t, len = v.size();
        if (l == 0) {
            for (i = 1; i < len; i++)
                for (j = 0; j < len - i; j++)
                    if (v[j] > v[j + 1]) {
                        t = v[j];
                        v[j] = v[j + 1];
                        v[j + 1] = t;

                    }
        } else {
            for (i = 1; i < len; i++)
                for (j = 0; j < len - i; j++)
                    if (v[j] < v[j + 1]) {
                        t = v[j];
                        v[j] = v[j + 1];
                        v[j + 1] = t;
                    }
        }
    }
}