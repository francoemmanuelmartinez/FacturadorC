#pragma once
#include "..\Models\Proveedor.h"
#include "..\Models\Usuario.h"
#include "..\Servicios\Conexion.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaProveedorABM.h"
#include "..\Vistas\VistaFormulario.h"
#include "..\Filtros\ValidadorMail.h"
#include "..\Filtros\ValidadorCampos.h"

namespace Controladores {
    ref class ControladorAdmin;
    ref class ControladorLogin;
}

using namespace Models;
using namespace Servicios;
using namespace Vistas;
using namespace Filtros;
using namespace MySql::Data::MySqlClient;

namespace Controladores {
    public ref class ControladorProveedorABM {
    private:
        Conexion^ c;
        Usuario^ usuario;
        VentanaPrincipal^ ventanaPrincipal;
        VistaProveedorABM^ vista;
        int filtroActual;

        void volverButton_Click(Object^ sender, EventArgs^ e);

        Proveedor^ mapearProveedor(MySqlDataReader^ rs) {
            auto p = gcnew Proveedor();
            p->Id = safe_cast<int>(rs["id"]);
            p->Nombre = rs["nombre"]->ToString();
            p->Telefono = rs["telefono"]->ToString();
            p->Direccion = rs["direccion"]->ToString();
            p->Mail = rs["mail"]->ToString();
            p->Habilitado = safe_cast<int>(rs["habilitado"]);
            return p;
        }

        void poblarTabla() {
            vista->tablaProveedores->Columns->Clear();
            vista->tablaProveedores->Columns->Add(L"ID", L"ID");
            vista->tablaProveedores->Columns->Add(L"Nombre", L"Nombre");
            vista->tablaProveedores->Columns->Add(L"Telefono", L"Telefono");
            vista->tablaProveedores->Columns->Add(L"Direccion", L"Direccion");
            vista->tablaProveedores->Columns->Add(L"Mail", L"Mail");
            vista->tablaProveedores->Columns->Add(L"Habilitado", L"Habilitado");
            vista->tablaProveedores->Columns[5]->Visible = false;

            vista->tablaProveedores->Rows->Clear();
            auto proveedores = obtenerProveedoresPorHabilitado(filtroActual);
            for each (Proveedor^ p in proveedores) {
                vista->tablaProveedores->Rows->Add(p->Id, p->Nombre, p->Telefono, p->Direccion, p->Mail, p->Habilitado);
            }
        }

        void comboBoxChanged(Object^ sender, EventArgs^ e) {
            filtroActual = vista->comboBoxFiltroHabilitado->SelectedIndex == 0 ? 1 : 0;
            poblarTabla();
            vista->deshabilitarButton->Text = filtroActual == 1 ? L"Deshabilitar" : L"Habilitar";
        }

        void buscarButton_Click(Object^ sender, EventArgs^ e) {
            String^ texto = this->vista->textFieldID->Text->Trim();
            if (String::IsNullOrEmpty(texto)) { this->poblarTabla(); return; }
            int id;
            if (Int32::TryParse(texto, id)) {
                auto p = this->buscarProveedor(id, this->filtroActual);
                if (p != nullptr) {
                    this->vista->tablaProveedores->Rows->Clear();
                    this->vista->tablaProveedores->Rows->Add(p->Id, p->Nombre, p->Telefono, p->Direccion, p->Mail, p->Habilitado);
                }
            }
        }

        void agregarButton_Click(Object^ sender, EventArgs^ e) {
            auto valores = VistaFormulario::mostrarDialogo(L"Nuevo Proveedor",
                gcnew VistaFormulario::Campo(L"Nombre:", L"", L"Texto", true),
                gcnew VistaFormulario::Campo(L"Telefono:", L"", L"Numerico", true),
                gcnew VistaFormulario::Campo(L"Direccion:", L"", L"Alfanumerico", true),
                gcnew VistaFormulario::Campo(L"Mail:", L"", L"Alfanumerico", true)
            );
            if (valores != nullptr) {
                if (this->agregarProveedor(valores[L"Nombre:"], valores[L"Telefono:"],
                    valores[L"Direccion:"], valores[L"Mail:"]) > -1) this->poblarTabla();
            }
        }

        void modificarButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tablaProveedores->SelectedRows->Count == 0) {
                MessageBox::Show(L"Seleccione un proveedor de la tabla"); return;
            }
            auto fila = this->vista->tablaProveedores->SelectedRows[0];
            int idProveedor = safe_cast<int>(fila->Cells[0]->Value);
            auto valores = VistaFormulario::mostrarDialogo(L"Modificar Proveedor",
                gcnew VistaFormulario::Campo(L"Nombre:", fila->Cells[1]->Value->ToString(), L"Texto", true),
                gcnew VistaFormulario::Campo(L"Telefono:", fila->Cells[2]->Value->ToString(), L"Numerico", true),
                gcnew VistaFormulario::Campo(L"Direccion:", fila->Cells[3]->Value->ToString(), L"Alfanumerico", true),
                gcnew VistaFormulario::Campo(L"Mail:", fila->Cells[4]->Value->ToString(), L"Alfanumerico", true)
            );
            if (valores != nullptr) {
                if (this->modificarProveedor(idProveedor, valores[L"Nombre:"], valores[L"Telefono:"],
                    valores[L"Direccion:"], valores[L"Mail:"])) this->poblarTabla();
            }
        }

        void deshabilitarButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tablaProveedores->SelectedRows->Count == 0) {
                MessageBox::Show(L"Seleccione un proveedor de la tabla"); return;
            }
            auto fila = this->vista->tablaProveedores->SelectedRows[0];
            int idProveedor = safe_cast<int>(fila->Cells[0]->Value);
            int habilitadoActual = safe_cast<int>(fila->Cells[5]->Value);
            String^ nuevoEstado = habilitadoActual == 1 ? L"deshabilitar" : L"habilitar";
            auto result = MessageBox::Show(L"?Esta seguro de " + nuevoEstado + L" al proveedor con ID " + idProveedor + L"?",
                nuevoEstado == L"deshabilitar" ? L"Deshabilitar Proveedor" : L"Habilitar Proveedor", MessageBoxButtons::YesNo);
            if (result == DialogResult::Yes) {
                if (this->toggleHabilitadoProveedor(idProveedor)) this->poblarTabla();
            }
        }

    public:
        ControladorProveedorABM() : c(gcnew Conexion()), filtroActual(1) {}

        ControladorProveedorABM(Usuario^ usuario, VentanaPrincipal^ ventanaPrincipal) : c(gcnew Conexion()), filtroActual(1) {
            this->usuario = usuario;
            this->ventanaPrincipal = ventanaPrincipal;
            vista = gcnew VistaProveedorABM();
            ventanaPrincipal->setVista(vista->panelProveedorABM);

            poblarTabla();
            vista->comboBoxFiltroHabilitado->SelectedIndexChanged += gcnew EventHandler(this, &ControladorProveedorABM::comboBoxChanged);
            vista->buscarButton->Click += gcnew EventHandler(this, &ControladorProveedorABM::buscarButton_Click);
            vista->agregarButton->Click += gcnew EventHandler(this, &ControladorProveedorABM::agregarButton_Click);
            vista->modificarButton->Click += gcnew EventHandler(this, &ControladorProveedorABM::modificarButton_Click);
            vista->deshabilitarButton->Click += gcnew EventHandler(this, &ControladorProveedorABM::deshabilitarButton_Click);
            vista->volverButton->Click += gcnew EventHandler(this, &ControladorProveedorABM::volverButton_Click);
        }

        List<Proveedor^>^ obtenerProveedoresPorHabilitado(int habilitado) {
            auto proveedores = gcnew List<Proveedor^>();
            c->conectar();
            String^ sql = "SELECT id, nombre, telefono, direccion, mail, habilitado FROM proveedores WHERE habilitado = ?habilitado";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?habilitado", habilitado);
            auto rs = cmd->ExecuteReader();
            while (rs->Read()) proveedores->Add(mapearProveedor(rs));
            rs->Close();
            return proveedores;
        }

        Proveedor^ buscarProveedor(int id, int habilitado) {
            c->conectar();
            String^ sql = "SELECT id, nombre, telefono, direccion, mail, habilitado FROM proveedores WHERE id = ?id AND habilitado = ?habilitado";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?id", id);
            cmd->Parameters->AddWithValue("?habilitado", habilitado);
            auto rs = cmd->ExecuteReader();
            Proveedor^ p = nullptr;
            if (rs->Read()) p = mapearProveedor(rs);
            else MessageBox::Show(L"No existe el proveedor con ese ID");
            rs->Close();
            return p;
        }

        int agregarProveedor(String^ nombre, String^ telefono, String^ direccion, String^ mail) {
            String^ requeridos = ValidadorCampos::validarRequeridos(
                L"Nombre", nombre, L"Telefono", telefono, L"Direccion", direccion, L"Mail", mail);
            if (requeridos != nullptr) { MessageBox::Show(L"Campos requeridos: " + requeridos); return -1; }

            if (!ValidadorMail::esValido(mail)) {
                MessageBox::Show(L"El formato del mail no es valido"); return -1;
            }

            c->conectar();
            String^ sqlSelect = "SELECT mail FROM proveedores WHERE mail = ?mail";
            auto cmdSelect = gcnew MySqlCommand(sqlSelect, c->con);
            cmdSelect->Parameters->AddWithValue("?mail", mail);
            auto reader = cmdSelect->ExecuteReader();
            if (reader->Read()) { MessageBox::Show(L"Este mail ya ha sido registrado"); reader->Close(); return -1; }
            reader->Close();

            String^ sqlInsert = "INSERT INTO proveedores(nombre, telefono, direccion, mail) VALUES(?nombre, ?telefono, ?direccion, ?mail)";
            auto cmd = gcnew MySqlCommand(sqlInsert, c->con);
            cmd->Parameters->AddWithValue("?nombre", nombre);
            cmd->Parameters->AddWithValue("?telefono", telefono);
            cmd->Parameters->AddWithValue("?direccion", direccion);
            cmd->Parameters->AddWithValue("?mail", mail);
            cmd->ExecuteNonQuery();
            int id = safe_cast<int>(cmd->LastInsertedId);
            MessageBox::Show(L"Proveedor agregado exitosamente");
            return id;
        }

        bool modificarProveedor(int id, String^ nombre, String^ telefono, String^ direccion, String^ mail) {
            String^ requeridos = ValidadorCampos::validarRequeridos(
                L"Nombre", nombre, L"Telefono", telefono, L"Direccion", direccion, L"Mail", mail);
            if (requeridos != nullptr) { MessageBox::Show(L"Campos requeridos: " + requeridos); return false; }

            if (!ValidadorMail::esValido(mail)) {
                MessageBox::Show(L"El formato del mail no es valido"); return false;
            }

            c->conectar();
            String^ sqlSelect = "SELECT mail FROM proveedores WHERE mail = ?mail AND id != ?id";
            auto cmdSelect = gcnew MySqlCommand(sqlSelect, c->con);
            cmdSelect->Parameters->AddWithValue("?mail", mail);
            cmdSelect->Parameters->AddWithValue("?id", id);
            auto reader = cmdSelect->ExecuteReader();
            if (reader->Read()) { MessageBox::Show(L"Ese mail ya pertenece a otro proveedor"); reader->Close(); return false; }
            reader->Close();

            String^ sqlUpdate = "UPDATE proveedores SET nombre=?nombre, telefono=?telefono, direccion=?direccion, mail=?mail WHERE id=?id";
            auto cmd = gcnew MySqlCommand(sqlUpdate, c->con);
            cmd->Parameters->AddWithValue("?nombre", nombre);
            cmd->Parameters->AddWithValue("?telefono", telefono);
            cmd->Parameters->AddWithValue("?direccion", direccion);
            cmd->Parameters->AddWithValue("?mail", mail);
            cmd->Parameters->AddWithValue("?id", id);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Proveedor modificado exitosamente");
            return true;
        }

        bool toggleHabilitadoProveedor(int id) {
            c->conectar();
            String^ sql = "UPDATE proveedores SET habilitado = CASE WHEN habilitado = 1 THEN 0 ELSE 1 END WHERE id = ?id";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?id", id);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Estado cambiado exitosamente");
            return true;
        }
    };
}
