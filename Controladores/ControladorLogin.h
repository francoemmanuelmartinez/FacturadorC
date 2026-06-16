#pragma once
#include "..\Models\Usuario.h"
#include "..\Servicios\Conexion.h"
#include "..\Servicios\Autenticacion.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaLogin.h"

namespace Controladores {
    ref class ControladorAdmin;
    ref class ControladorCajero;
    ref class ControladorDepositoABM;
    ref class ControladorRegistro;
}

using namespace Models;
using namespace Servicios;
using namespace Vistas;
using namespace MySql::Data::MySqlClient;

namespace Controladores {
    public ref class ControladorLogin {
    private:
        String^ mail;
        String^ password;
        String^ sql;
        Conexion^ c;
        Usuario^ usuario;
        VistaLogin^ vistaLogin;
        VentanaPrincipal^ ventanaPrincipal;

        void botonLogin_Click(Object^ sender, EventArgs^ e);
        void botonRegistrar_Click(Object^ sender, EventArgs^ e);
        void logear();

    public:
        ControladorLogin() : sql(L"SELECT id, nombre, apellido, dni, telefono, direccion, mail, rol, password FROM usuarios WHERE mail = ?"), c(gcnew Conexion()), usuario(gcnew Usuario()) {}

        ControladorLogin(VentanaPrincipal^ ventanaPrincipal) : sql(L"SELECT id, nombre, apellido, dni, telefono, direccion, mail, rol, password FROM usuarios WHERE mail = ?"), c(gcnew Conexion()), usuario(gcnew Usuario()) {
            this->ventanaPrincipal = ventanaPrincipal;
            vistaLogin = gcnew VistaLogin();
            ventanaPrincipal->setVista(vistaLogin->panelLogin);

            vistaLogin->botonLogin->Click += gcnew EventHandler(this, &ControladorLogin::botonLogin_Click);
            vistaLogin->botonRegistrar->Click += gcnew EventHandler(this, &ControladorLogin::botonRegistrar_Click);
        }

        bool validar(String^ mail, String^ password) {
            this->mail = mail;
            this->password = password;

            c->conectar();

            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?mail", mail);
            auto reader = cmd->ExecuteReader();

            if (reader->Read()) {
                usuario->Id = reader["id"]->ToString();
                usuario->Nombre = reader["nombre"]->ToString();
                usuario->Apellido = reader["apellido"]->ToString();
                usuario->Dni = reader["dni"]->ToString();
                usuario->Telefono = reader["telefono"]->ToString();
                usuario->Direccion = reader["direccion"]->ToString();
                usuario->Mail = reader["mail"]->ToString();
                usuario->Rol = reader["rol"]->ToString();
                usuario->Password = reader["password"]->ToString();
            }
            reader->Close();

            auto autenticacion = gcnew Autenticacion(mail, password);
            return autenticacion->autenticar(usuario);
        }
    };
}
