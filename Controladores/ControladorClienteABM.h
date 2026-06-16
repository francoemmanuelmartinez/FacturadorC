#pragma once
#include "..\Models\Cliente.h"
#include "..\Models\Usuario.h"
#include "..\Servicios\Conexion.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaClienteABM.h"
#include "..\Vistas\VistaFormulario.h"

namespace Controladores {
    ref class ControladorAdmin;
    ref class ControladorFactura;
}

using namespace Models;
using namespace Servicios;
using namespace Vistas;
using namespace MySql::Data::MySqlClient;

namespace Controladores {
    public ref class ControladorClienteABM {
    private:
        Conexion^ c;
        Usuario^ usuario;
        VentanaPrincipal^ ventanaPrincipal;
        VistaClienteABM^ vista;
        int filtroActual;

        void botonVolver_Click(Object^ sender, EventArgs^ e);
        void mostrarFacturasButton_Click(Object^ sender, EventArgs^ e);

        Cliente^ mapearCliente(MySqlDataReader^ rs) {
            auto cl = gcnew Cliente();
            cl->Id = safe_cast<int>(rs["id"]);
            cl->Nombre = rs["nombre"]->ToString();
            cl->Apellido = rs["apellido"]->ToString();
            cl->Dni = rs["dni"]->ToString();
            cl->Telefono = rs["telefono"]->ToString();
            cl->Direccion = rs["direccion"]->ToString();
            cl->Mail = rs["mail"]->ToString();
            cl->Habilitado = safe_cast<int>(rs["habilitado"]);
            return cl;
        }

        void poblarTabla() {
            vista->tablaClientes->Columns->Clear();
            vista->tablaClientes->Columns->Add(L"ID", L"ID");
            vista->tablaClientes->Columns->Add(L"Nombre", L"Nombre");
            vista->tablaClientes->Columns->Add(L"Apellido", L"Apellido");
            vista->tablaClientes->Columns->Add(L"DNI", L"DNI");
            vista->tablaClientes->Columns->Add(L"Telefono", L"Telefono");
            vista->tablaClientes->Columns->Add(L"Direccion", L"Direccion");
            vista->tablaClientes->Columns->Add(L"Mail", L"Mail");
            vista->tablaClientes->Columns->Add(L"Habilitado", L"Habilitado");
            vista->tablaClientes->Columns[7]->Visible = false;
            vista->tablaClientes->Columns[0]->Visible = false;

            vista->tablaClientes->Rows->Clear();
            auto clientes = obtenerClientesPorHabilitado(filtroActual);
            for each (Cliente^ cl in clientes) {
                vista->tablaClientes->Rows->Add(cl->Id, cl->Nombre, cl->Apellido, cl->Dni, cl->Telefono, cl->Direccion, cl->Mail, cl->Habilitado);
            }
        }

        void comboBoxChanged(Object^ sender, EventArgs^ e) {
            filtroActual = vista->comboBoxFiltroHabilitado->SelectedIndex == 0 ? 1 : 0;
            poblarTabla();
            vista->eliminarButton->Text = filtroActual == 1 ? L"Deshabilitar" : L"Habilitar";
        }

        void buscar_Click(Object^ sender, EventArgs^ e) {
            String^ texto = this->vista->dniTF->Text->Trim();
            if (String::IsNullOrEmpty(texto)) {
                this->poblarTabla();
            }
            else {
                auto cl = this->buscarCliente(texto, this->filtroActual);
                if (cl != nullptr) {
                    this->vista->tablaClientes->Rows->Clear();
                    this->vista->tablaClientes->Rows->Add(cl->Id, cl->Nombre, cl->Apellido, cl->Dni, cl->Telefono, cl->Direccion, cl->Mail, cl->Habilitado);
                }
            }
        }

        void agregar_Click(Object^ sender, EventArgs^ e) {
            auto valores = VistaFormulario::mostrarDialogo(L"Nuevo Cliente",
                gcnew VistaFormulario::Campo(L"Nombre:"),
                gcnew VistaFormulario::Campo(L"Apellido:"),
                gcnew VistaFormulario::Campo(L"DNI:"),
                gcnew VistaFormulario::Campo(L"Telefono:"),
                gcnew VistaFormulario::Campo(L"Direccion:"),
                gcnew VistaFormulario::Campo(L"Mail:")
            );
            if (valores != nullptr) {
                int id = this->agregarCliente(valores[L"Nombre:"], valores[L"Apellido:"], valores[L"DNI:"],
                    valores[L"Telefono:"], valores[L"Direccion:"], valores[L"Mail:"]);
                if (id > -1) this->poblarTabla();
            }
        }

        void modificar_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tablaClientes->SelectedRows->Count == 0) {
                MessageBox::Show(L"Seleccione un cliente de la tabla");
                return;
            }
            auto fila = this->vista->tablaClientes->SelectedRows[0];
            int idCliente = safe_cast<int>(fila->Cells[0]->Value);

            auto valores = VistaFormulario::mostrarDialogo(L"Modificar Cliente",
                gcnew VistaFormulario::Campo(L"Nombre:", fila->Cells[1]->Value->ToString()),
                gcnew VistaFormulario::Campo(L"Apellido:", fila->Cells[2]->Value->ToString()),
                gcnew VistaFormulario::Campo(L"DNI:", fila->Cells[3]->Value->ToString()),
                gcnew VistaFormulario::Campo(L"Telefono:", fila->Cells[4]->Value->ToString()),
                gcnew VistaFormulario::Campo(L"Direccion:", fila->Cells[5]->Value->ToString()),
                gcnew VistaFormulario::Campo(L"Mail:", fila->Cells[6]->Value->ToString())
            );
            if (valores != nullptr) {
                if (this->modificarCliente(idCliente, valores[L"Nombre:"], valores[L"Apellido:"], valores[L"DNI:"],
                    valores[L"Telefono:"], valores[L"Direccion:"], valores[L"Mail:"])) {
                    this->poblarTabla();
                }
            }
        }

        void eliminar_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tablaClientes->SelectedRows->Count == 0) {
                MessageBox::Show(L"Seleccione un cliente de la tabla");
                return;
            }
            auto fila = this->vista->tablaClientes->SelectedRows[0];
            int idCliente = safe_cast<int>(fila->Cells[0]->Value);
            int habilitadoActual = safe_cast<int>(fila->Cells[7]->Value);
            String^ nuevoEstado = habilitadoActual == 1 ? L"deshabilitar" : L"habilitar";

            auto result = MessageBox::Show(L"?Esta seguro de " + nuevoEstado + L" al cliente con ID " + idCliente + L"?",
                nuevoEstado == L"deshabilitar" ? L"Deshabilitar Cliente" : L"Habilitar Cliente", MessageBoxButtons::YesNo);
            if (result == DialogResult::Yes) {
                if (this->toggleHabilitadoCliente(idCliente)) this->poblarTabla();
            }
        }

    public:
        ControladorClienteABM() : c(gcnew Conexion()), filtroActual(1) {}

        ControladorClienteABM(Usuario^ usuario, VentanaPrincipal^ ventanaPrincipal) : c(gcnew Conexion()), filtroActual(1) {
            this->usuario = usuario;
            this->ventanaPrincipal = ventanaPrincipal;
            vista = gcnew VistaClienteABM();
            ventanaPrincipal->setVista(vista->panelClienteABM);

            poblarTabla();

            vista->comboBoxFiltroHabilitado->SelectedIndexChanged += gcnew EventHandler(this, &ControladorClienteABM::comboBoxChanged);
            vista->botonBuscar->Click += gcnew EventHandler(this, &ControladorClienteABM::buscar_Click);
            vista->agregarButton->Click += gcnew EventHandler(this, &ControladorClienteABM::agregar_Click);
            vista->modificarButton->Click += gcnew EventHandler(this, &ControladorClienteABM::modificar_Click);
            vista->eliminarButton->Click += gcnew EventHandler(this, &ControladorClienteABM::eliminar_Click);
            vista->botonVolver->Click += gcnew EventHandler(this, &ControladorClienteABM::botonVolver_Click);
            vista->mostrarFacturasButton->Click += gcnew EventHandler(this, &ControladorClienteABM::mostrarFacturasButton_Click);
        }

        List<Cliente^>^ obtenerClientesPorHabilitado(int habilitado) {
            auto clientes = gcnew List<Cliente^>();
            c->conectar();
            String^ sql = "SELECT id, nombre, apellido, dni, telefono, direccion, mail, habilitado FROM clientes WHERE habilitado = ?habilitado";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?habilitado", habilitado);
            auto rs = cmd->ExecuteReader();
            while (rs->Read()) clientes->Add(mapearCliente(rs));
            rs->Close();
            return clientes;
        }

        Cliente^ buscarCliente(String^ dni, int habilitado) {
            c->conectar();
            String^ sql = "SELECT id, nombre, apellido, dni, telefono, direccion, mail, habilitado FROM clientes WHERE dni = ?dni AND habilitado = ?habilitado";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?dni", dni);
            cmd->Parameters->AddWithValue("?habilitado", habilitado);
            auto rs = cmd->ExecuteReader();
            Cliente^ cliente = nullptr;
            if (rs->Read()) cliente = mapearCliente(rs);
            else MessageBox::Show(L"No existe el cliente con ese dni");
            rs->Close();
            return cliente;
        }

        int agregarCliente(String^ nombre, String^ apellido, String^ dni, String^ telefono, String^ direccion, String^ mail) {
            c->conectar();
            String^ sqlSelect = "SELECT mail FROM clientes WHERE mail = ?mail";
            auto cmdSelect = gcnew MySqlCommand(sqlSelect, c->con);
            cmdSelect->Parameters->AddWithValue("?mail", mail);
            auto reader = cmdSelect->ExecuteReader();
            if (reader->Read()) { MessageBox::Show(L"Este mail ya ha sido registrado"); reader->Close(); return -1; }
            reader->Close();

            String^ sqlInsert = "INSERT INTO clientes(nombre, apellido, dni, telefono, direccion, mail) VALUES(?nombre, ?apellido, ?dni, ?telefono, ?direccion, ?mail)";
            auto cmd = gcnew MySqlCommand(sqlInsert, c->con);
            cmd->Parameters->AddWithValue("?nombre", nombre);
            cmd->Parameters->AddWithValue("?apellido", apellido);
            cmd->Parameters->AddWithValue("?dni", dni);
            cmd->Parameters->AddWithValue("?telefono", telefono);
            cmd->Parameters->AddWithValue("?direccion", direccion);
            cmd->Parameters->AddWithValue("?mail", mail);
            cmd->ExecuteNonQuery();
            int id = safe_cast<int>(cmd->LastInsertedId);
            MessageBox::Show(L"Cliente agregado exitosamente");
            return id;
        }

        bool modificarCliente(int id, String^ nombre, String^ apellido, String^ dni, String^ telefono, String^ direccion, String^ mail) {
            c->conectar();
            String^ sqlSelect = "SELECT mail FROM clientes WHERE mail = ?mail AND id != ?id";
            auto cmdSelect = gcnew MySqlCommand(sqlSelect, c->con);
            cmdSelect->Parameters->AddWithValue("?mail", mail);
            cmdSelect->Parameters->AddWithValue("?id", id);
            auto reader = cmdSelect->ExecuteReader();
            if (reader->Read()) { MessageBox::Show(L"Ese mail ya pertenece a otro cliente"); reader->Close(); return false; }
            reader->Close();

            String^ sqlUpdate = "UPDATE clientes SET nombre=?nombre, apellido=?apellido, dni=?dni, telefono=?telefono, direccion=?direccion, mail=?mail WHERE id=?id";
            auto cmd = gcnew MySqlCommand(sqlUpdate, c->con);
            cmd->Parameters->AddWithValue("?nombre", nombre); cmd->Parameters->AddWithValue("?apellido", apellido);
            cmd->Parameters->AddWithValue("?dni", dni); cmd->Parameters->AddWithValue("?telefono", telefono);
            cmd->Parameters->AddWithValue("?direccion", direccion); cmd->Parameters->AddWithValue("?mail", mail);
            cmd->Parameters->AddWithValue("?id", id);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Cliente modificado exitosamente");
            return true;
        }

        bool toggleHabilitadoCliente(int id) {
            c->conectar();
            String^ sql = "UPDATE clientes SET habilitado = CASE WHEN habilitado = 1 THEN 0 ELSE 1 END WHERE id = ?id";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?id", id);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Estado cambiado exitosamente");
            return true;
        }
    };
}
