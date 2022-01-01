#include <Windows.h>
#include <iostream>
#include <vector>

class UniqueWcs
{
public:
    UniqueWcs() : Vectors{} {};

    VOID Dup(std::unique_ptr<WCHAR[]> &Pointer, const PWSTR Source)
    {
        std::unique_ptr<WCHAR[]> newPtr = std::unique_ptr<WCHAR[]>(new WCHAR[MAX_PATH]);
        PWSTR pointer = newPtr.get();
        wcscpy_s(pointer, MAX_PATH, Source);
        Pointer = std::move(newPtr);
    }

    VOID RealDup(PWSTR *Dest, const PWSTR Source)
    {
        std::unique_ptr<WCHAR[]> newPtr = std::unique_ptr<WCHAR[]>(new WCHAR[MAX_PATH]);
        Vectors.push_back(NULL);
        Vectors.back() = std::move(newPtr);
        wcscpy_s(Vectors.back().get(), MAX_PATH, Source);
        *Dest = Vectors.back().get();
    }

    PWSTR Dup(PCWSTR Source)
    {
        std::unique_ptr<WCHAR[]> newPtr = std::unique_ptr<WCHAR[]>(new WCHAR[MAX_PATH]);
        Vectors.push_back(NULL);
        Vectors.back() = std::move(newPtr);
        wcscpy_s(Vectors.back().get(), MAX_PATH, Source);
        return(Vectors.back().get());
    }

private:
    std::vector<std::unique_ptr<WCHAR[]>> Vectors;
};

int main()
{
    std::cout << "Hello Unique WCS!\n";

    UniqueWcs uniqueWcs;

    std::vector<std::unique_ptr<WCHAR[]>> pws;

    PWSTR pw;

    std::unique_ptr<WCHAR[]> pu;

    uniqueWcs.Dup(pu, (PWSTR)L"Test1");
    printf("%ws\n", pu.get());

    uniqueWcs.Dup(pu, (PWSTR)L"Test2");
    printf("%ws\n", pu.get());


    uniqueWcs.RealDup(&pw, (PWSTR)L"Test3");
    printf("%ws\n", pw);

    uniqueWcs.RealDup(&pw, (PWSTR)L"Test4");
    printf("%ws\n", pw);


    pw = uniqueWcs.Dup((PCWSTR)L"Test5");
    printf("%ws\n", pw);

    pw = uniqueWcs.Dup((PCWSTR)L"Test6");
    printf("%ws\n", pw);

}
