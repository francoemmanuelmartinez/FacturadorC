#pragma once
#include "..\Models\Usuario.h"
#include "..\Servicios\Conexion.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaUsuarioABM.h"
#include "..\Vistas\VistaFormulario.h"
#include "..\Filtros\ValidadorCampos.h"
#include "..\Filtros\ValidadorMail.h"
#include "..\Filtros\ValidadorCantidadAdmin.h"

namespace Controladores { ref class ControladorAdmin; }

using namespace Models;
using namespace Servicios;
using namespace Vistas;
using namespace MySql::Data::MySqlClient;

namespace Controladores {
    public ref class ControladorUsuarioABM {
    private:
        Conexion^ c;
        Usuario^ usuario;
        VentanaPrincipal^ ventanaPrincipal;
        VistaUsuarioABM^ vista;
        int filtroActual;

        void volverButton_Click(Object^ sender, EventArgs^ e);

        void poblarTabla() {
            vista->tablaUsuarios->Columns->Clear();
            vista->tablaUsuarios->Columns->Add(L"Nombre", L"Nombre");
            vista->tablaUsuarios->Columns->Add(L"Apellido", L"Apellido");
            vista->tablaUsuarios->Columns->Add(L"Dni", L"Dni");
            vista->tablaUsuarios->Columns->Add(L"Telefono", L"Telefono");
            vista->tablaUsuarios->Columns->Add(L"Direccion", L"Direccion");
            vista->tablaUsuarios->Columns->Add(L"Mail", L"Mail");
            vista->tablaUsuarios->Columns->Add(L"Rol", L"Rol");
            vista->tablaUsuarios->Columns->Add(L"Password", L"Password");
            vista->tablaUsuarios->Columns->Add(L"Habilitado", L"Habilitado");
            vista->tablaUsuarios->Columns[8]->Visible = false;

            vista->tablaUsuarios->Rows->Clear();
            auto usuarios = obtenerUsuariosPorHabilitado(filtroActual);
            for each (Usuario^ u in usuarios) {
                int rowIdx = vista->tablaUsuarios->Rows->Add(u->Nombre, u->Apellido, u->Dni, u->Telefono, u->Direccion, u->Mail, u->Rol, u->Password, u->Habilitado);
                vista->tablaUsuarios->Rows[rowIdx]->Tag = u->Id;
            }
        }

        void comboBoxChanged(Object^ sender, EventArgs^ e) {
            filtroActual = vista->comboBoxFiltroHabilitado->SelectedIndex == 0 ? 1 : 0;
            poblarTabla();
            vista->eliminarButton->Text = filtroActual == 1 ? L"Deshabilitar" : L"Habilitar";
        }

        void botonBuscar_Click(Object^ sender, EventArgs^ e) {
            String^ texto = this->vista->dniTF->Text->Trim();
            if (String::IsNullOrEmpty(texto)) { this->poblarTabla(); return; }
            auto u = this->buscarUsuario(texto, this->filtroActual);
            if (u != nullptr) {
                this->vista->tablaUsuarios->Rows->Clear();
                int rowIdx = this->vista->tablaUsuarios->Rows->Add(u->Nombre, u->Apellido, u->Dni, u->Telefono, u->Direccion, u->Mail, u->Rol, u->Password, u->Habilitado);
                this->vista->tablaUsuarios->Rows[rowIdx]->Tag = u->Id;
            }
        }

        void agregarButton_Click(Object^ sender, EventArgs^ e) {
            auto valores = VistaFormulario::mostrarDialogo(L"Nuevo Usuario",
                gcnew VistaFormulario::Campo(L"Nombre:", L"", L"Texto", true), gcnew VistaFormulario::Campo(L"Apellido:", L"", L"Texto", true),
                gcnew VistaFormulario::Campo(L"DNI:", L"", L"Numerico", true), gcnew VistaFormulario::Campo(L"Telefono:", L"", L"Numerico"),
                gcnew VistaFormulario::Campo(L"Direccion:", L"", L"Alfanumerico"), gcnew VistaFormulario::Campo(L"Mail:", L"", L"Alfanumerico", true),
                gcnew VistaFormulario::Campo(L"Contrasena:", true, true),
                gcnew VistaFormulario::Campo(L"Rol:", gcnew array<String^> { L"Administrador", L"Cajero", L"Deposito" }, true)
            );
            if (valores != nullptr) {
                String^ error = ValidadorCampos::validarRequeridos(
                    L"Nombre", valores[L"Nombre:"],
                    L"Apellido", valores[L"Apellido:"],
                    L"DNI", valores[L"DNI:"],
                    L"Telefono", valores[L"Telefono:"],
                    L"Direccion", valores[L"Direccion:"],
                    L"Mail", valores[L"Mail:"],
                    L"Contrasena", valores[L"Contrasena:"],
                    L"Rol", valores[L"Rol:"]
                );
                if (error != nullptr) { MessageBox::Show(L"Campos requeridos: " + error); return; }
                if (!ValidadorMail::esValido(valores[L"Mail:"])) { MessageBox::Show(L"Mail invalido"); return; }
                if (valores[L"Contrasena:"]->Length < 6) { MessageBox::Show(L"La contrasena debe tener al menos 6 caracteres"); return; }
                if (this->agregarUsuario(valores[L"Nombre:"], valores[L"Apellido:"], valores[L"DNI:"], valores[L"Telefono:"],
                    valores[L"Direccion:"], valores[L"Mail:"], valores[L"Contrasena:"], valores[L"Rol:"])) this->poblarTabla();
            }
        }

        void modificarButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tablaUsuarios->SelectedRows->Count == 0) { MessageBox::Show(L"Seleccione un usuario de la tabla"); return; }
            auto fila = this->vista->tablaUsuarios->SelectedRows[0];
            int idUsuario = Convert::ToInt32(fila->Tag);
            String^ dniOriginal = fila->Cells[2]->Value->ToString();

            auto valores = VistaFormulario::mostrarDialogo(L"Modificar Usuario",
                gcnew VistaFormulario::Campo(L"Nombre:", fila->Cells[0]->Value->ToString(), L"Texto", true),
                gcnew VistaFormulario::Campo(L"Apellido:", fila->Cells[1]->Value->ToString(), L"Texto", true),
                gcnew VistaFormulario::Campo(L"DNI:", dniOriginal, L"Numerico", true),
                gcnew VistaFormulario::Campo(L"Telefono:", fila->Cells[3]->Value->ToString(), L"Numerico"),
                gcnew VistaFormulario::Campo(L"Direccion:", fila->Cells[4]->Value->ToString(), L"Alfanumerico"),
                gcnew VistaFormulario::Campo(L"Mail:", fila->Cells[5]->Value->ToString(), L"Alfanumerico", true),
                gcnew VistaFormulario::Campo(L"Rol:", gcnew array<String^> { L"Administrador", L"Cajero", L"Deposito" }, fila->Cells[6]->Value->ToString(), true),
                gcnew VistaFormulario::Campo(L"Contrasena:", true, fila->Cells[7]->Value->ToString())
            );
            if (valores != nullptr) {
                String^ error = ValidadorCampos::validarRequeridos(
                    L"Nombre", valores[L"Nombre:"],
                    L"Apellido", valores[L"Apellido:"],
                    L"DNI", valores[L"DNI:"],
                    L"Telefono", valores[L"Telefono:"],
                    L"Direccion", valores[L"Direccion:"],
                    L"Mail", valores[L"Mail:"],
                    L"Contrasena", valores[L"Contrasena:"],
                    L"Rol", valores[L"Rol:"]
                );
                if (error != nullptr) { MessageBox::Show(L"Campos requeridos: " + error); return; }
                if (!ValidadorMail::esValido(valores[L"Mail:"])) { MessageBox::Show(L"Mail invalido"); return; }
                if (valores[L"Contrasena:"]->Length < 6) { MessageBox::Show(L"La contrasena debe tener al menos 6 caracteres"); return; }
                String^ rolActual = fila->Cells[6]->Value->ToString();
                if (rolActual == L"Administrador" && valores[L"Rol:"] != L"Administrador") {
                    if (!ValidadorCantidadAdmin::permitirCambiarRol(idUsuario)) return;
                }
                if (this->modificarUsuario(idUsuario, valores[L"Nombre:"], valores[L"Apellido:"], valores[L"DNI:"],
                    valores[L"Telefono:"], valores[L"Direccion:"], valores[L"Mail:"], valores[L"Rol:"], valores[L"Contrasena:"])) this->poblarTabla();
            }
        }

        void eliminarButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tablaUsuarios->SelectedRows->Count == 0) { MessageBox::Show(L"Seleccione un usuario de la tabla"); return; }
            auto fila = this->vista->tablaUsuarios->SelectedRows[0];
            String^ dni = fila->Cells[2]->Value->ToString();
            int habilitadoActual = safe_cast<int>(fila->Cells[8]->Value);
            String^ nuevoEstado = habilitadoActual == 1 ? L"deshabilitar" : L"habilitar";
            if (habilitadoActual == 1 && fila->Cells[6]->Value->ToString() == L"Administrador") {
                int idActual = Convert::ToInt32(fila->Tag);
                if (!ValidadorCantidadAdmin::permitirDeshabilitar(idActual)) return;
            }
            auto result = MessageBox::Show(L"?Esta seguro de " + nuevoEstado + L" al usuario con DNI " + dni + L"?",
                nuevoEstado == L"deshabilitar" ? L"Deshabilitar Usuario" : L"Habilitar Usuario", MessageBoxButtons::YesNo);
            if (result == DialogResult::Yes) { if (this->toggleHabilitado(dni)) this->poblarTabla(); }
        }

    public:
        ControladorUsuarioABM() : c(gcnew Conexion()), filtroActual(1) {}

        ControladorUsuarioABM(Usuario^ usuario, VentanaPrincipal^ ventanaPrincipal) : c(gcnew Conexion()), filtroActual(1) {
            this->usuario = usuario;
            this->ventanaPrincipal = ventanaPrincipal;
            vista = gcnew VistaUsuarioABM();
            ventanaPrincipal->setVista(vista->panelUsuarioABM);

            poblarTabla();
            vista->comboBoxFiltroHabilitado->SelectedIndexChanged += gcnew EventHandler(this, &ControladorUsuarioABM::comboBoxChanged);

            vista->botonBuscar->Click += gcnew EventHandler(this, &ControladorUsuarioABM::botonBuscar_Click);
            vista->agregarButton->Click += gcnew EventHandler(this, &ControladorUsuarioABM::agregarButton_Click);
            vista->modificarButton->Click += gcnew EventHandler(this, &ControladorUsuarioABM::modificarButton_Click);
            vista->eliminarButton->Click += gcnew EventHandler(this, &ControladorUsuarioABM::eliminarButton_Click);
            vista->volverButton->Click += gcnew EventHandler(this, &ControladorUsuarioABM::volverButton_Click);
        }

        List<Usuario^>^ obtenerUsuariosPorHabilitado(int habilitado) {
            auto usuarios = gcnew List<Usuario^>();
            c->conectar();
            String^ sql = "SELECT id, nombre, apellido, dni, telefono, direccion, mail, rol, password, habilitado FROM usuarios WHERE habilitado = ?habilitado";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?habilitado", habilitado);
            auto rs = cmd->ExecuteReader();
            while (rs->Read()) {
                auto u = gcnew Usuario();
                u->Id = rs["id"]->ToString(); u->Nombre = rs["nombre"]->ToString(); u->Apellido = rs["apellido"]->ToString();
                u->Dni = rs["dni"]->ToString(); u->Telefono = rs["telefono"]->ToString();
                u->Direccion = rs["direccion"]->ToString(); u->Mail = rs["mail"]->ToString();
                u->Rol = rs["rol"]->ToString(); u->Password = rs["password"]->ToString();
                u->Habilitado = safe_cast<int>(rs["habilitado"]);
                usuarios->Add(u);
            }
            rs->Close();
            return usuarios;
        }

        bool agregarUsuario(String^ nombre, String^ apellido, String^ dni, String^ telefono, String^ direccion, String^ mail, String^ password, String^ rol) {
            c->conectar();
            String^ sqlDni = "SELECT dni FROM usuarios WHERE dni = ?dni";
            auto cmdDni = gcnew MySqlCommand(sqlDni, c->con);
            cmdDni->Parameters->AddWithValue("?dni", dni);
            auto readerDni = cmdDni->ExecuteReader();
            if (readerDni->Read()) { MessageBox::Show(L"Ya existe un usuario con ese DNI"); readerDni->Close(); return false; }
            readerDni->Close();

            String^ sqlSelect = "SELECT mail FROM usuarios WHERE mail = ?mail";
            auto cmdSelect = gcnew MySqlCommand(sqlSelect, c->con);
            cmdSelect->Parameters->AddWithValue("?mail", mail);
            auto reader = cmdSelect->ExecuteReader();
            if (reader->Read()) { MessageBox::Show(L"Este mail ya ha sido registrado"); reader->Close(); return false; }
            reader->Close();

            String^ sqlInsert = "INSERT INTO usuarios(nombre, apellido, dni, telefono, direccion, mail, rol, password) VALUES(?nombre, ?apellido, ?dni, ?telefono, ?direccion, ?mail, ?rol, ?password)";
            auto cmd = gcnew MySqlCommand(sqlInsert, c->con);
            cmd->Parameters->AddWithValue("?nombre", nombre); cmd->Parameters->AddWithValue("?apellido", apellido);
            cmd->Parameters->AddWithValue("?dni", dni); cmd->Parameters->AddWithValue("?telefono", telefono);
            cmd->Parameters->AddWithValue("?direccion", direccion); cmd->Parameters->AddWithValue("?mail", mail);
            cmd->Parameters->AddWithValue("?rol", rol); cmd->Parameters->AddWithValue("?password", password);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Usuario agregado exitosamente");
            return true;
        }

        bool modificarUsuario(int idUsuario, String^ nombre, String^ apellido, String^ dni, String^ telefono, String^ direccion, String^ mail, String^ rol, String^ password) {
            c->conectar();
            String^ sqlDni = "SELECT dni FROM usuarios WHERE dni = ?dni AND id != ?id";
            auto cmdDni = gcnew MySqlCommand(sqlDni, c->con);
            cmdDni->Parameters->AddWithValue("?dni", dni);
            cmdDni->Parameters->AddWithValue("?id", idUsuario);
            auto readerDni = cmdDni->ExecuteReader();
            if (readerDni->Read()) { MessageBox::Show(L"Ese DNI ya pertenece a otro usuario"); readerDni->Close(); return false; }
            readerDni->Close();

            String^ sqlSelect = "SELECT mail FROM usuarios WHERE mail = ?mail AND id != ?id";
            auto cmdSelect = gcnew MySqlCommand(sqlSelect, c->con);
            cmdSelect->Parameters->AddWithValue("?mail", mail);
            cmdSelect->Parameters->AddWithValue("?id", idUsuario);
            auto reader = cmdSelect->ExecuteReader();
            if (reader->Read()) { MessageBox::Show(L"Ese mail ya pertenece a otro usuario"); reader->Close(); return false; }
            reader->Close();

            String^ sqlUpdate = "UPDATE usuarios SET nombre=?nombre, apellido=?apellido, dni=?dni, telefono=?telefono, direccion=?direccion, mail=?mail, rol=?rol, password=?password WHERE id=?id";
            auto cmd = gcnew MySqlCommand(sqlUpdate, c->con);
            cmd->Parameters->AddWithValue("?nombre", nombre); cmd->Parameters->AddWithValue("?apellido", apellido);
            cmd->Parameters->AddWithValue("?dni", dni); cmd->Parameters->AddWithValue("?telefono", telefono);
            cmd->Parameters->AddWithValue("?direccion", direccion); cmd->Parameters->AddWithValue("?mail", mail);
            cmd->Parameters->AddWithValue("?rol", rol); cmd->Parameters->AddWithValue("?password", password);
            cmd->Parameters->AddWithValue("?id", idUsuario);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Usuario modificado exitosamente");
            return true;
        }

        bool toggleHabilitado(String^ dni) {
            c->conectar();
            String^ sql = "UPDATE usuarios SET habilitado = CASE WHEN habilitado = 1 THEN 0 ELSE 1 END WHERE dni = ?dni";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?dni", dni);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Estado cambiado exitosamente");
            return true;
        }

        Usuario^ buscarUsuario(String^ dni, int habilitado) {
            c->conectar();
            String^ sql = "SELECT id, nombre, apellido, dni, telefono, direccion, mail, rol, password, habilitado FROM usuarios WHERE dni = ?dni AND habilitado = ?habilitado";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?dni", dni);
            cmd->Parameters->AddWithValue("?habilitado", habilitado);
            auto reader = cmd->ExecuteReader();
            Usuario^ u = nullptr;
            if (reader->Read()) {
                u = gcnew Usuario();
                u->Id = reader["id"]->ToString(); u->Nombre = reader["nombre"]->ToString(); u->Apellido = reader["apellido"]->ToString();
                u->Dni = reader["dni"]->ToString(); u->Telefono = reader["telefono"]->ToString();
                u->Direccion = reader["direccion"]->ToString(); u->Mail = reader["mail"]->ToString();
                u->Rol = reader["rol"]->ToString(); u->Password = reader["password"]->ToString();
                u->Habilitado = safe_cast<int>(reader["habilitado"]);
            }
            else MessageBox::Show(L"No existe el usuario con el dni");
            reader->Close();
            return u;
        }
    };
}
