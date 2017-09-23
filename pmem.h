#ifndef P_MEM_H
#define P_MEM_H

#include <cstddef>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <ostream>

namespace Plib {

    class Pmem {
        std::shared_ptr<char> str;
        static int ObjCount;

        void alloc_string(size_t);

        bool tempAllocated;
        friend std::ostream &operator<<(std::ostream &, Pmem);

        friend std::istream &operator>>(std::istream &, Pmem &);

    public:
        const static unsigned Ascend;
        const static unsigned Descend;
        const static unsigned AlphaC;
        const static unsigned AlphaS;
        const static unsigned Num;
        std::shared_ptr<char> temp;

        unsigned getCurrentOwnerCount();

        static int objectCount();

        void allocTemp(size_t);

        void sync();

        Pmem();

        Pmem(size_t);

        Pmem(const char *);

        Pmem(Pmem *);

        ~Pmem();

        std::string getStdString();

        char *getCString();

        void assign(const char *);

        void assign(Pmem);

        void assign(std::string);

        Pmem append(Pmem);

        Pmem append(const char *);

        Pmem append(std::string);

        void write(size_t = 0);

        void read();

        size_t size();

        void assignTo(Pmem &);

        void appendTo(Pmem &);

        Pmem slice(size_t, size_t);

        bool operator!=(Pmem);

        bool operator==(Pmem);

        bool operator>=(Pmem);

        bool operator<=(Pmem);

        bool operator>(Pmem);

        bool operator<(Pmem);

        void operator=(Pmem);

        void operator=(std::string);

        void operator=(const char *);

        bool contain(Pmem);

        long long find(Pmem);

        long long findLast(Pmem);

        Pmem caseUp();

        Pmem caseDown();

        Pmem caseTitle();

        size_t findAll(std::vector<size_t> &, Pmem);

        Pmem replace(Pmem, Pmem);

        Pmem replace(size_t, size_t, Pmem);

        long long findExcept(Pmem);

        void clear();

        bool containAfter(size_t, Pmem);

        bool containBefore(size_t, Pmem);

        bool containWithin(size_t, size_t, Pmem);

        Pmem replaceFromPattern(std::vector<size_t>, size_t, Pmem);

        Pmem remove(Pmem);

        Pmem remove(size_t, size_t);

        Pmem removeFromPattern(std::vector<size_t>, size_t);

        void swap(Pmem &);

        void reverse();

        Pmem operator-();

        Pmem insert(size_t, Pmem);

        Pmem pop(size_t = 1);

        Pmem operator[](size_t);

        static Pmem randomString(size_t, const int);

        long long toLongLong();

        size_t toSize_t();

        int toInt();

        double toDouble();

        char toChar();

        static void sort(std::vector<size_t> &, int);

        static Pmem import(long long);

        static Pmem import(size_t);

        static Pmem import(char);

        static Pmem import(double);

        static Pmem import(int);

        static Pmem import(const char *);

        static Pmem import(std::string);
};
}
#endif /* Pmem_H_ */
