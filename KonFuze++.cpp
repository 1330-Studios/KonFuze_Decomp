#include <iomanip>

#include "KonFuze.h"

int main() {
    KonFuze::StaticConstructor();

    const auto example_kon_fuze = new KonFuze(80);

    example_kon_fuze->Add(45.84);
    example_kon_fuze->Add(45.11);

    printf("%f", example_kon_fuze->Read());
}