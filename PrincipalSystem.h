//
// Created by kaosj on 22/02/2026.
//

#ifndef PARCIAL_1_PRINCIPALSYSTEM_H
#define PARCIAL_1_PRINCIPALSYSTEM_H
#include <cstring>
#include <iostream>
#include <limits>
using namespace std;

class PrincipalSystem {
    //Estructura para controlar reservas
    struct aulasReserva {
        string nombre;
        string fecha;
        int hora;
        int duracion;
        bool asignado;
        aulasReserva * siguiente;

        aulasReserva(string nom, string date, int h, int dur, bool asig = false) : nombre(nom), duracion(dur), hora(h), asignado(asig), fecha(date), siguiente(nullptr) {}
    };

    //Estructura para manejar el sistema de colas
    struct colas {
        aulasReserva * frente;
        aulasReserva * final;
        int tamaño;

        colas() : frente(nullptr), final(nullptr), tamaño(0) {};
    };

    //Estructura para manejar la informacion de las aulas
    struct infoAulas {
        char nombre[50];
        int capacidad;
        bool disponible;
        colas * colaReserva;
        infoAulas * siguiente;

        infoAulas(const char* name, int capacity) :capacidad(capacity), disponible(true), colaReserva(new colas()), siguiente(nullptr) {
            strcpy(nombre, name);
        }
    };

    infoAulas * cabeza = nullptr;


    //Funcion auxiliar para buscar aulas por nombre
    infoAulas * buscarAula(const char*n) {
        infoAulas * actual = cabeza;
        while (actual!= nullptr) {
            if (strcmp(actual->nombre, n) == 0 ) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    bool hayConflictoHorario(colas * cola, string fechaNueva, int horaNueva, int duracionNueva) {
        aulasReserva * actual = cola -> frente;
        while (actual!= nullptr) {
            if (actual-> fecha == fechaNueva) {
                if (actual->hora < horaNueva + duracionNueva && horaNueva < actual->hora + actual -> duracion) {
                    return true;
                }
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void encolarReservas(infoAulas * aula, string nombre, string fecha, int hora, int duracion, bool asignado = false) {
        aulasReserva * nuevoNodo = new aulasReserva(nombre, fecha, hora, duracion, asignado);
        nuevoNodo -> siguiente = nullptr;
        if (aula->colaReserva->frente == nullptr) {
            aula->colaReserva->frente = nuevoNodo;
            aula->colaReserva->final = nuevoNodo;
        } else {
            aula->colaReserva->final->siguiente = nuevoNodo;
            aula->colaReserva->final = nuevoNodo;
        }
        aula->colaReserva->tamaño++;
    }

    void mostrarHorariosDisponibles(infoAulas * aula, string fecha) {
        cout << "Los horarios disponibles para " << aula -> nombre << " Son: " << fecha << ":" << endl;
        for (int h = 6; h < 22; h++) {
            bool ocupado = false;
            aulasReserva * actual = aula -> colaReserva -> frente;
            while (actual!= nullptr) {
                if (actual -> fecha == fecha) {
                    if (h >= actual -> hora && h < actual -> hora + actual -> duracion) {
                        ocupado = true;
                        break;
                    }
                }
                actual = actual -> siguiente;
            }
            if (!ocupado) {
                cout << h << ":00 - " << h + 1 << ":00" << endl;
            }
        }
    }

    void reservarAula(const char * nombreAula, string nombreUsuario, const char * f, int h, int dur, int cantPersonas) {
        infoAulas * aula = buscarAula(nombreAula);
        if (aula == nullptr) {
            cout << "Aula no encontrada" << endl;
            return;
        }
        if (cantPersonas > aula -> capacidad) {
            cout << "Cantidad de personas supera la capacidad del aula" << endl;
            return;
        }
        if (aula -> disponible) {
            aula -> disponible = false;
            encolarReservas(aula, nombreUsuario, f, h, dur, true);
            cout << "Aula reservada exitosamente a "  << nombreUsuario << endl;
        } else {                                                              // ← desde aqui
            if (hayConflictoHorario(aula->colaReserva, f, h, dur)) {
                cout << "Ese horario ya esta ocupado" << endl;
                cout << "1. Encolarse para ese horario" << endl;
                cout << "2. Ver otros horarios disponibles" << endl;
                cout << "Ingrese una opcion: ";
                int opcionReserva;
                cin >> opcionReserva;

                if (opcionReserva == 1) {
                    encolarReservas(aula, nombreUsuario, f, h, dur);
                    cout << "Ha sido encolado para las " << h << ":00 - " << h + dur << ":00 el " << f << endl;
                } else {
                    mostrarHorariosDisponibles(aula, f);
                }
            } else {
                encolarReservas(aula, nombreUsuario, f, h, dur);
                cout << "Su reserva ha sido encolada para las " << h << ":00 - " << h + dur << ":00 el " << f << endl;
            }
        }
    }

    void cancelarReserva(const char * nombre, string usuario) {
        infoAulas * aula = buscarAula(nombre);
        if (aula == nullptr) {
            cout << "Reserva del aula: " << nombre << " Inexistente" << endl;
            return;
        }
        aulasReserva * actual = aula -> colaReserva -> frente;
        aulasReserva *anterior = nullptr;
        while (actual!= nullptr) {
            if (actual->nombre == usuario && actual->asignado == true) {
                if (anterior == nullptr) {
                    aula->colaReserva->frente = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                aula->colaReserva->tamaño--;

                if (aula->colaReserva->frente != nullptr) {
                    aula->colaReserva->frente->asignado = true;
                    cout << "El aula fue asignada al siguiente en cola" << endl;
                } else {
                    aula->disponible = true;
                    cout << "El aula queda disponible" << endl;
                }
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        cout << "No se encontro una reserva activa para " << usuario << endl;
    }

    void verReservas(string usuario) {
        infoAulas * actualAula = cabeza;
        bool encontrado = false;
        while (actualAula != nullptr) {
            aulasReserva * actualReserva = actualAula -> colaReserva -> frente;
            while (actualReserva != nullptr) {
                if (actualReserva->nombre == usuario && actualReserva->asignado == true) {
                    cout << "Aula: " << actualAula->nombre << endl;
                    cout << "Fecha: " << actualReserva->fecha << endl;
                    cout << "Hora: " << actualReserva->hora << ":00" << endl;
                    cout << "Duracion: " << actualReserva->duracion << " horas" << endl;
                    cout << "------------------------" << endl;
                    encontrado = true;
                }
                actualReserva = actualReserva -> siguiente;
            }
            actualAula = actualAula -> siguiente;
        }
        if (!encontrado) {
            cout << "No tienes reservas activas" << endl;
        }
    }

    void mostrarTodasAulas() {
        infoAulas * actual = cabeza;
        if (actual == nullptr) {
            cout << "No hay aulas registradas aun" << endl;
        }
        while (actual != nullptr) {
            cout << "Aula: " << actual->nombre
             << "\n\tCapacidad: " << actual->capacidad
             << "\n\tEstado: " << (actual->disponible ? "Disponible" : "Ocupada")
             << "\n\tPersonas en cola: " << actual->colaReserva->tamaño
             << "\n------------------------" << endl;
            actual = actual->siguiente;
        }
    }

public:
    void insertarAulas (const char*n, int c) {
        infoAulas * nuevaAula = new infoAulas(n, c);
        nuevaAula->siguiente = cabeza;
        cabeza = nuevaAula;
    }

    void menu() {
        int opcion;
        cout << "\n=== Bienvenido Al Sistema de Reserva de Aulas ===" << endl;
        cout << "1. Reservar un aula" << endl;
        cout << "2. Consultar estado de todas las aulas" << endl;
        cout << "3. Ver mis reservas activas" << endl;
        cout << "4. Cancelar una reserva" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        while (opcion != 5) {
            switch (opcion) {
                case 1: {
                    char nombreAula[50];
                    string usuario;
                    string fecha;
                    int hora;
                    int duracion;
                    int cantPersonas;
                    cout << "=== Reservar Aula ===" << endl;
                    cout << "Nombre del aula: ";
                    cin >> nombreAula;
                    cout << "Nombre del usuario: ";
                    cin.ignore();
                    getline(cin, usuario);
                    cout << "Fecha (DD/MM/AAAA): ";
                    cin >> fecha;
                    cout << "Hora (6-22): ";
                    cin >> hora;
                    cout << "Duracion (horas): ";
                    cin >> duracion;
                    cout << "Cantidad de personas: ";
                    cin >> cantPersonas;
                    reservarAula(nombreAula, usuario, fecha.c_str(), hora, duracion, cantPersonas);
                    cout << "\nPresione Enter para volver al menu...";
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 2:
                    mostrarTodasAulas();
                    cout << "\nPresione para volver al menu...";
                    cin.ignore();
                    cin.get();
                    break;
                case 3: {
                    string usuario;
                    cout << "Ingrese su nombre: ";
                    cin.ignore();
                    getline(cin, usuario);
                    verReservas(usuario);
                    cout << "\nPresione Enter dos veces para volver al menu...";
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 4: {
                    char nombreAula[50];
                    string usuario;
                    cout << "Ingrese su nombre de usuario: ";
                    cin.ignore();
                    getline(cin, usuario);
                    cout << "Ingrese el nombre del aula: ";
                    cin >> nombreAula;
                    cancelarReserva(nombreAula, usuario);
                    break;
                }
                default:
                    cout << "Opcion invalida" << endl;
                    break;
            }

            cout << "\n=== Bienvenido Al Sistema de Reserva de Aulas ===" << endl;
            cout << "1. Reservar un aula" << endl;
            cout << "2. Consultar estado de todas las aulas" << endl;
            cout << "3. Ver mis reservas activas" << endl;
            cout << "4. Cancelar una reserva" << endl;
            cout << "5. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion;
        }
        cout << "Gracias por usar nuestro sistema!" << endl;
    }

};

#endif //PARCIAL_1_PRINCIPALSYSTEM_H