#pragma once
#include "..\Servicios\Conexion.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaRegistro.h"

namespace Controladores { ref class ControladorLogin; }

using namespace Servicios;
using namespace Vistas;
using namespace MySql::Data::MySqlClient;

namespace Controladores {
    public ref class ControladorRegistro {
    private:
        Conexion^ c;
        String^ sqlInsert;
        VistaRegistro^ vistaRegistro;
        VentanaPrincipal^ ventanaPrincipal;

        void registrarse_Click(Object^ sender, EventArgs^ e);
        void botonVolver_Click(Object^ sender, EventArgs^ e);

    public:
        ControladorRegistro() : c(gcnew Conexion()), sqlInsert(L"INSERT INTO usuarios(nombre, apellido, dni, telefono, direccion, mail, rol, password) VALUES(?nombre, ?apellido, ?dni, ?telefono, ?direccion, ?mail, 3, ?password)") {}

        ControladorRegistro(VentanaPrincipal^ ventanaPrincipal) : c(gcnew Conexion()), sqlInsert(L"INSERT INTO usuarios(nombre, apellido, dni, telefono, direccion, mail, rol, password) VALUES(?nombre, ?apellido, ?dni, ?telefono, ?direccion, ?mail, 3, ?password)") {
            this->ventanaPrincipal = ventanaPrincipal;
            vistaRegistro = gcnew VistaRegistro();
            ventanaPrincipal->setVista(vistaRegistro->panelRegistro);

            vistaRegistro->registrarse->Click += gcnew EventHandler(this, &ControladorRegistro::registrarse_Click);
            vistaRegistro->botonVolver->Click += gcnew EventHandler(this, &ControladorRegistro::botonVolver_Click);
        }

        bool registrar(String^ nombre, String^ apellido, String^ dni, String^ telefono, String^ direccion, String^ mail, String^ password) {
            try {
                c->conectar();

                String^ sqlSelect = "SELECT mail FROM usuarios WHERE mail = ?mail";
                auto cmdSelect = gcnew MySqlCommand(sqlSelect, c->con);
                cmdSelect->Parameters->AddWithValue("?mail", mail);
                auto reader = cmdSelect->ExecuteReader();
                if (reader->Read()) {
                    MessageBox::Show(L"Este mail ya ha sido registrado");
                    reader->Close();
                    return false;
                }
                reader->Close();

                auto cmd = gcnew MySqlCommand(sqlInsert, c->con);
                cmd->Parameters->AddWithValue("?nombre", nombre);
                cmd->Parameters->AddWithValue("?apellido", apellido);
                cmd->Parameters->AddWithValue("?dni", dni);
                cmd->Parameters->AddWithValue("?telefono", telefono);
                cmd->Parameters->AddWithValue("?direccion", direccion);
                cmd->Parameters->AddWithValue("?mail", mail);
                cmd->Parameters->AddWithValue("?password", password);
                cmd->ExecuteNonQuery();
                MessageBox::Show(L"Registro exitoso");
                return true;
            }
            catch (Exception^ ex) {
                throw gcnew Exception(ex->Message);
            }
        }
    };
}
