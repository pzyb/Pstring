#ifndef PSTRING_H
#define PSTRING_H

#include <iostream>
#include <cstddef>
#include <cstring>
#include <vector>
#include <ctime>
#include <sstream>

namespace Plib {
    class Pstring {
    protected:
        bool isAlloc;
        std::string str;

        friend std::ostream &operator<<(std::ostream &, Pstring);

        friend std::istream &operator>>(std::istream &, Pstring &);

    public:
        const static unsigned Ascend;
        const static unsigned Descend;
        const static unsigned AlphaC;
        const static unsigned AlphaS;
        const static unsigned Num;
        char *tmp;

        void allocTemp(size_t);

        void deallocTemp();

        void sync();

        std::string getStdString();

        char *getCString();

        Pstring();

        ~Pstring();

        Pstring(const char *);

        Pstring(std::string);

        void assign(const char *);

        void assign(Pstring);

        void assign(std::string);

        Pstring append(Pstring);

        Pstring append(const char *);

        Pstring append(std::string);

        void write(long long = 0);

        void read();

        size_t size();

        void assignTo(Pstring &);

        void appendTo(Pstring &);

        Pstring slice(size_t, size_t);

        bool operator!=(Pstring);

        bool operator==(Pstring);

        bool operator>=(Pstring);

        bool operator<=(Pstring);

        bool operator>(Pstring);

        bool operator<(Pstring);

        void operator=(Pstring);

        void operator=(std::string);

        void operator=(const char *);

        bool contain(Pstring);

        long long find(Pstring);

        Pstring caseUp();

        Pstring caseDown();

        Pstring caseTitle();

        long long findLast(Pstring);

        size_t findAll(std::vector<size_t> &, Pstring);

        Pstring replace(Pstring, Pstring);

        Pstring replace(size_t, size_t, Pstring);

        long long findExcept(Pstring);

        void clear();

        bool containAfter(size_t, Pstring);

        bool containBefore(size_t, Pstring);

        bool containWithin(size_t, size_t, Pstring);

        Pstring replaceFromPattern(std::vector<size_t>, size_t, Pstring);

        Pstring remove(Pstring);

        Pstring remove(size_t, size_t);

        Pstring removeFromPattern(std::vector<size_t>, size_t);

        void swap(Pstring &);

        void reverse();

        Pstring operator-();

        Pstring insert(size_t, Pstring);

        Pstring pop(size_t = 1);

        Pstring operator[](size_t);

        Pstring operator+(Pstring);

        void operator+=(Pstring);

        Pstring operator-(Pstring);

        void operator-=(Pstring);

        static Pstring randomString(size_t, const int);

        long long toLongLong();

        size_t toSize_t();

        int toInt();

        double toDouble();

        char toChar();

        static void sort(std::vector<size_t> &, int);

        static Pstring import(long long);

        static Pstring import(size_t);

        static Pstring import(char);

        static Pstring import(double);

        static Pstring import(int);

        static Pstring import(const char *);

        static Pstring import(std::string);
    };
}
#endif
