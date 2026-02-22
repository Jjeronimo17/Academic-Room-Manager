//
// Created by kaosj on 22/02/2026.
//

#include "PrincipalSystem.h"
#include <iostream>
using namespace std;

int main() {
    PrincipalSystem sistema;
    sistema.insertarAulas("Salon101", 30);
    sistema.insertarAulas("Salon102", 20);
    sistema.insertarAulas("Salon103", 50);
    sistema.insertarAulas("LaboratorioA", 25);
    sistema.insertarAulas("Auditorio", 100);
    sistema.insertarAulas("LaboratorioSistemas", 20);
    sistema.insertarAulas("LaboratorioRedes", 20);
    sistema.insertarAulas("LaboratorioFisica", 15);
    sistema.insertarAulas("Auditorio", 200);
    sistema.insertarAulas("SalaConferencias", 50);
    sistema.insertarAulas("SalaReuniones", 10);
    sistema.insertarAulas("BibliotecaSala1", 30);
    sistema.insertarAulas("BibliotecaSala2", 30);
    sistema.insertarAulas("TallerIngenieria", 25);
    sistema.menu();

}