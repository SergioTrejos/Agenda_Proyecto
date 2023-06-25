#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct Evento {
    string fecha;
    string hora;
};

void registrarUsuario(const string& nombreUsuario, const string& contrasena) {
    ofstream archivoUsuarios("usuarios.txt", ios::app);
    if (archivoUsuarios.is_open()) {
        archivoUsuarios << nombreUsuario << " " << contrasena << endl;
        archivoUsuarios.close();
        cout << "Usuario registrado correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo de usuarios." << endl;
    }
}

bool verificarCredenciales(const string& nombreUsuario, const string& contrasena) {
    ifstream archivoUsuarios("usuarios.txt");
    string usuario, password;

    while (archivoUsuarios >> usuario >> password) {
        if (usuario == nombreUsuario && password == contrasena) {
            archivoUsuarios.close();
            return true;
        }
    }

    archivoUsuarios.close();
    return false;
}

void resetearContrasena(const string& nombreUsuario) {
    ofstream archivoTemporal("temporal.txt");

    if (!archivoTemporal.is_open()) {
        cout << "Error al abrir el archivo temporal." << endl;
        return;
    }

    ifstream archivoUsuarios("usuarios.txt");
    string usuario, contrasena;

    while (archivoUsuarios >> usuario >> contrasena) {
        if (usuario == nombreUsuario) {
            string nuevaContrasena;
            cout << "Ingrese la nueva contraseña: ";
            cin >> nuevaContrasena;
            archivoTemporal << usuario << " " << nuevaContrasena << endl;
            cout << "Contraseña restablecida correctamente." << endl;
        } else {
            archivoTemporal << usuario << " " << contrasena << endl;
        }
    }

    archivoUsuarios.close();
    archivoTemporal.close();

    remove("usuarios.txt");
    rename("temporal.txt", "usuarios.txt");
}

void verEventos() {
    ifstream archivoEventos("eventos.txt");
    string linea;

    cout << "Eventos creados:" << endl;

    while (getline(archivoEventos, linea)) {
        cout << linea << endl;
    }

    archivoEventos.close();
}

void agendarEvento() {
    string fecha, hora;

    cout << "Agendar evento" << endl;
    cout << "Fecha (dd/mm/aaaa): ";
    cin >> fecha;
    cout << "Hora (hh:mm): ";
    cin >> hora;

    string evento = "Fecha: " + fecha + " Hora: " + hora;
    ofstream archivoEventos("eventos.txt", ios::app);
    if (archivoEventos.is_open()) {
        archivoEventos << evento << endl;
        archivoEventos.close();
        cout << "Evento agendado correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo de eventos." << endl;
    }
}

int main() {
    int opcion;
    string nombreUsuario, contrasena;
    bool sesionIniciada = false;

    cout << "Bienvenido!" << endl;

    while (true) {
        if (!sesionIniciada) {
            cout << "\nSeleccione una opción:" << endl;
            cout << "1. Iniciar sesión" << endl;
            cout << "2. Registrarse" << endl;
            cout << "3. Restablecer contraseña" << endl;
        } else {
            cout << "\nSeleccione una opción:" << endl;
            cout << "1. Cerrar sesión" << endl;
            cout << "2. Ver eventos" << endl;
            cout << "3. Agendar evento" << endl;
            cout << "4. Otra opción después de iniciar sesión" << endl;
        }

        cout << "Opción: ";
        cin >> opcion;

        if (!sesionIniciada) {
            switch (opcion) {
                case 1:
                    cout << "Iniciar sesión" << endl;
                    cout << "Nombre de usuario: ";
                    cin >> nombreUsuario;
                    cout << "Contraseña: ";
                    cin >> contrasena;

                    if (verificarCredenciales(nombreUsuario, contrasena)) {
                        cout << "Inicio de sesión exitoso. ¡Bienvenido, " << nombreUsuario << "!" << endl;
                        sesionIniciada = true;
                    } else {
                        cout << "Credenciales incorrectas. No se pudo iniciar sesión." << endl;
                    }
                    break;

                case 2:
                    cout << "Registrarse" << endl;
                    cout << "Nombre de usuario: ";
                    cin >> nombreUsuario;

                    if (verificarCredenciales(nombreUsuario, "")) {
                        cout << "El nombre de usuario ya existe. Por favor, elige otro." << endl;
                    } else {
                        cout << "Contraseña: ";
                        cin >> contrasena;
                        registrarUsuario(nombreUsuario, contrasena);
                    }
                    break;

                case 3:
                    cout << "Restablecer contraseña" << endl;
                    cout << "Nombre de usuario: ";
                    cin >> nombreUsuario;
                    resetearContrasena(nombreUsuario);
                    break;

                default:
                    cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                    break;
            }
        } else {
            switch (opcion) {
                case 1:
                    cout << "Cerrando sesión. ¡Hasta luego, " << nombreUsuario << "!" << endl;
                    sesionIniciada = false;
                    break;

                case 2:
                    verEventos();
                    break;

                case 3:
                    agendarEvento();
                    break;

                case 4:
                    // Aquí puedes agregar las opciones adicionales después de iniciar sesión
                    cout << "Otra opción después de iniciar sesión seleccionada." << endl;
                    break;

                default:
                    cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                    break;
            }
        }
    }

    return 0;
}