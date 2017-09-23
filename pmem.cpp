#include <time.h>
#include "Pmem.h"

namespace Plib {
    int Pmem::ObjCount = 0;
    const unsigned Pmem::Ascend = 0;
    const unsigned Pmem::Descend = 1;
    const unsigned Pmem::AlphaC = 10;
    const unsigned Pmem::AlphaS = 100;
    const unsigned Pmem::Num = 1000;

    Pmem Pmem::pop(size_t sz) {
        Pmem tmp;
        tmp = slice(size() - sz, size() - 1);
        remove(size() - sz, size() - 1);
        return tmp;
    }

    char *Pmem::getCString() {
        return str.get();
    }

    std::string Pmem::getStdString() {
        return std::string(str.get());
    }

    void Pmem::sync() {
        assign(temp.get());
    }

    void Pmem::clear() {
        assign("");
    }

    int Pmem::objectCount() {
        return ObjCount;
    }

    void Pmem::alloc_string(size_t sz) {
        str.reset(new char[sz], [](char *s) {
            delete[] s;
        });
    }

    void Pmem::allocTemp(size_t sz) {
        tempAllocated = true;
        temp.reset(new char[sz], [](char *s) {
            delete[] s;
        });
    }

    Pmem::Pmem() :
            tempAllocated(false), temp(NULL) {
        allocTemp(1);
        alloc_string(1);
        strcpy(str.get(), "");
        ObjCount++;
    }

    Pmem::~Pmem() {
        ObjCount--;
    }

    Pmem::Pmem(size_t sz) :
            tempAllocated(false), temp(NULL) {
        alloc_string(sz);
        ObjCount++;
    }

    Pmem::Pmem(Pmem *st) :
            tempAllocated(false), temp(NULL) {
        assign(st);
        ObjCount++;
    }

    Pmem::Pmem(const char *st) :
            tempAllocated(false), temp(NULL) {
        assign(st);
        ObjCount++;
    }

    void Pmem::assign(const char *st) {
        if (str.get() != st) {
            str.reset();
            alloc_string(strlen(st) + 1);
            strcpy(str.get(), st);
        }
    }

    void Pmem::assign(Pmem st) {
        assign(st.str.get());
    }

    void Pmem::assign(std::string st) {
        assign(st.c_str());
    }

    Pmem Pmem::append(std::string st) {
        return append(st.c_str());
    }

    Pmem Pmem::append(const char *st) {
        if (st == str.get()) {
            char *Dat;
            Dat = new char[size() + 1];
            strcpy(Dat, str.get());
            str.reset();
            alloc_string(2 * strlen(Dat) + 1);
            strcpy(str.get(), Dat);
            strcat(str.get(), Dat);
            delete[] Dat;
        } else {
            char *Dat;
            Dat = new char[size() + 1];
            strcpy(Dat, str.get());
            str.reset();
            alloc_string(strlen(Dat) + strlen(st) + 1);
            strcpy(str.get(), Dat);
            strcat(str.get(), st);
            delete[] Dat;
        }
        return import(str.get());
    }

    void Pmem::operator=(Pmem st) {
        assign(st.str.get());
    }

    void Pmem::operator=(std::string st) {
        assign(st);
    }

    void Pmem::operator=(const char *st) {
        assign(st);
    }

    Pmem Pmem::append(Pmem st) {
        return append(st.str.get());
    }

    size_t Pmem::size() {
        return strlen(str.get());
    }

    void Pmem::write(size_t sz) {
        if (sz == 0)
            std::cout.write(str.get(), size());
        else
            std::cout.write(str.get(), sz);
    }

    void Pmem::assignTo(Pmem &st) {
        st.assign(str.get());
    }

    void Pmem::appendTo(Pmem &st) {
        st.append(str.get());
    }

    void Pmem::read() {
        clear();
        char c;
        while ((c = std::cin.get()) != '\n')
            append(import(c));
    }

    long long Pmem::toLongLong() {
        long long v;
        std::istringstream is(str.get());
        is >> v;
        return v;
    }

    int Pmem::toInt() {
        int v;
        std::istringstream is(str.get());
        is >> v;
        return v;
    }

    size_t Pmem::toSize_t() {
        size_t v;
        std::istringstream is(str.get());
        is >> v;
        return v;
    }

    double Pmem::toDouble() {
        double v;
        std::istringstream is(str.get());
        is >> v;
        return v;
    }

    char Pmem::toChar() {
        char v;
        std::istringstream is(str.get());
        is >> v;
        return v;
    }

    bool Pmem::contain(Pmem st) {
        Pmem tmp;
        long long i = 0;
        while (i + st.size() <= size()) {
            tmp = slice(i, i + st.size() - 1);
            if (tmp == st)
                return true;
            i++;
        }
        return false;
    }


    Pmem Pmem::import(char a) {
        std::ostringstream os;
        os << a;
        return import(os.str().c_str());
    }

    Pmem Pmem::import(const char *a) {
        return Pmem(a);
    }

    Pmem Pmem::import(long long a) {
        std::ostringstream os;
        os << a;
        return import(os.str().c_str());
    }

    Pmem Pmem::import(std::string s) {
        Pmem p;
        p.assign(s);
        return p;
    }

    Pmem Pmem::import(size_t a) {
        std::ostringstream os;
        os << a;
        return import(os.str().c_str());
    }

    Pmem Pmem::import(int a) {
        std::ostringstream os;
        os << a;
        return import(os.str().c_str());
    }

    Pmem Pmem::import(double a) {
        std::ostringstream os;
        os << a;
        return import(os.str().c_str());
    }

    bool Pmem::containAfter(size_t pos, Pmem st) {
        size_t s = 0, j = 0, i;
        for (i = pos; i < size(); i++) {
            if (str.get()[i] == st.str.get()[j]) {
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
            return 1;
        else
            return 0;
    }


    bool Pmem::containBefore(size_t pos, Pmem st) {
        size_t s = 0, j = 0, i;
        for (i = 0; i <= pos; i++) {
            if (str.get()[i] == st.str.get()[j]) {
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
            return 1;
        else
            return 0;
    }

    bool Pmem::containWithin(size_t pos1, size_t pos2, Pmem st) {
        size_t s = 0, j = 0, i;
        for (i = ((pos1 > pos2) ? pos2 : pos1); i <= ((pos1 > pos2) ? pos1 : pos2);
             i++) {
            if (str.get()[i] == st.str.get()[j]) {
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
            return 1;
        else
            return 0;
    }

    long long Pmem::find(Pmem st) {
        Pmem tmp;
        size_t i = 0;
        while (i + st.size() <= size()) {
            tmp = slice(i, i + st.size() - 1);
            if (tmp == st)
                return i;
            i++;
        }
        return -1;
    }

    long long Pmem::findLast(Pmem st) {
        Pmem tmp;
        st.reverse();
        Pmem rev = str.get();
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


    Pmem Pmem::operator-() {
        Pmem tmp;
        tmp.assign(str.get());
        tmp.reverse();
        return tmp;
    }


    long long Pmem::findExcept(Pmem st) {
        Pmem tmp;
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

    size_t Pmem::findAll(std::vector<size_t> &count, Pmem st) {
        Pmem tmp;
        size_t i = 0;
        while (i + st.size() <= size()) {
            tmp = slice(i, i + st.size() - 1);
            if (tmp == st)
                count.push_back(i);
            i++;
        }
        return count.size();
    }

    Pmem Pmem::slice(size_t a, size_t b) {
        if (b >= size()) {
            b = size()-1;
        }
            size_t i, j = 0;
            Pmem tmp(b-a+2);

            for (i = a; i <= b; i++) {
                tmp.str.get()[j++] = str.get()[i];
            }
            tmp.str.get()[j] = 0;
            return tmp;
    }

    Pmem Pmem::replace(size_t pos1, size_t pos2, Pmem to) {
        Pmem from;
        from = slice(pos1, pos2);
        long long i, k, j, l = 0;
        Pmem tmp;
        tmp = str.get();
        alloc_string(tmp.size() - (from.size()) + (to.size())+1);
        l = 0;
        j = 0;
        for (i = 0; i < tmp.size(); i++) {
            if (i == pos1) {
                for (k = 0; k < to.size(); k++) {
                    str.get()[l] = to.str.get()[k];
                    l++;
                }
                j++;
                i += from.size() - 1;
            } else {
                str.get()[l] = tmp.str.get()[i];
                l++;
            }
        }
        str.get()[l] = 0;
        return import(str.get());
    }

    Pmem Pmem::replace(Pmem from, Pmem to) {
        std::vector<size_t> val;
        size_t i, k, j, l = 0, len = findAll(val, from);
        Pmem tmp;
        tmp = str.get();
        if(len == 0)
            return Pmem(str.get());
        l = 0;
        j = 0;
        alloc_string(tmp.size() - (len * from.size()) + (len * to.size())+1);
        clear();
        for (i = 0; i < tmp.size(); i++) {
            if (i == val[j]) {
                for (k = 0; k < to.size(); k++) {
                    str.get()[l] = to.str.get()[k];
                    l++;
                }
                j++;
                i += from.size() - 1;
            } else {
                str.get()[l] = tmp.str.get()[i];
                l++;
            }
        }
        str.get()[l] = 0;
        return Pmem::import(str.get());
    }

    Pmem Pmem::replaceFromPattern(std::vector<size_t> val, size_t from, Pmem to) {
        sort(val, Pmem::Ascend);
        size_t i, k, j, l = 0, len = val.size();
        Pmem tmp;
        tmp = str.get();
        alloc_string(tmp.size() - (len * from) + (len * to.size())+1);
        l = 0;
        j = 0;
        for (i = 0; i < tmp.size(); i++) {
            if (i == val[j]) {
                for (k = 0; k < to.size(); k++) {
                    str.get()[l] = to.str.get()[k];
                    l++;
                }
                j++;
                i += from - 1;
            } else {
                str.get()[l] = tmp.str.get()[i];
                l++;
            }
        }
        str.get()[l] = 0;
        return import(str.get());
    }


    Pmem Pmem::remove(size_t pos1, size_t pos2) {
        return replace(pos1, pos2, Pmem(""));
    }

    Pmem Pmem::remove(Pmem st) {
        return replace(st, Pmem(""));
    }

    Pmem Pmem::removeFromPattern(std::vector<size_t> v, size_t from) {
        return replaceFromPattern(v, from, Pmem(""));
    }

    Pmem Pmem::caseUp() {
        for (size_t i = 0; i < size(); i++)
            if (islower(str.get()[i]))
                str.get()[i] = toupper(str.get()[i]);
        return import(str.get());
    }

    Pmem Pmem::caseDown() {
        for (size_t i = 0; i < size(); i++)
            if (isupper(str.get()[i]))
                str.get()[i] = tolower(str.get()[i]);
        return import(str.get());
    }

    Pmem Pmem::caseTitle() {
        str.get()[0] = toupper(str.get()[0]);
        for (unsigned long i = 0; i < size(); i++) {
            if (str.get()[i] == ' ' || str.get()[i] == '\t' || str.get()[i] == '.')
                str.get()[i + 1] = toupper(str.get()[i + 1]);
            else
                str.get()[i + 1] = tolower(str.get()[i + 1]);
        }
        return import(str.get());
    }

    Pmem Pmem::operator[](size_t v) {
        return import(str.get()[v]);
    }

    Pmem Pmem::insert(size_t pos, Pmem st) {
        if (pos >= size())
            pos = size();
        Pmem tmp;
        if (pos != 0)
            tmp.assign(slice(0, pos - 1));
        tmp.append(st);
        tmp.append(slice(pos, size() - 1));
        assign(tmp);
        return import(str.get());
    }

    Pmem Pmem::randomString(size_t sz, const int typ) {
        time_t t;
        Pmem st;
        srand((unsigned) time(&t));
        Pmem x;
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


    bool Pmem::operator!=(Pmem tmp) {
        if (strcmp(str.get(), tmp.str.get()) == 0)
            return 0;
        return 1;
    }

    bool Pmem::operator==(Pmem tmp) {
        if (strcmp(str.get(), tmp.str.get()) == 0)
            return 1;
        return 0;
    }


    bool Pmem::operator>=(Pmem tmp) {
        if (strcmp(str.get(), tmp.str.get()) >= 0)
            return 1;
        return 0;
    }


    bool Pmem::operator<=(Pmem tmp) {
        if (strcmp(str.get(), tmp.str.get()) <= 0)
            return 1;
        return 0;
    }


    bool Pmem::operator>(Pmem tmp) {
        if (strcmp(str.get(), tmp.str.get()) > 0)
            return 1;
        return 0;
    }


    bool Pmem::operator<(Pmem tmp) {
        if (strcmp(str.get(), tmp.str.get()) < 0)
            return 1;
        return 0;
    }


    void Pmem::reverse() {
        Pmem tmp(str.get());
        size_t i;
        for (i = 0; i < tmp.size(); i++)
            str.get()[i] = tmp.str.get()[tmp.size() - i - 1];
        str.get()[i] = '\0';
    }

    void Pmem::sort(std::vector<size_t> &v, int l) {
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

    void Pmem::swap(Pmem &st) {
        Pmem S;
        assignTo(S);
        assign(st);
        st.assign(S);
    }

    std::ostream &operator<<(std::ostream &os, Pmem ps) {
        return os << ps.str.get();
    }

    std::istream &operator>>(std::istream &is, Pmem &ps) {
        ps.alloc_string(1000);
        return is >> ps.str.get();
    }

    unsigned int Pmem::getCurrentOwnerCount() {
        return str.use_count();
    }
}