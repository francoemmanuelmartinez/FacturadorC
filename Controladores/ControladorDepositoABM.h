#pragma once
#include "..\Models\Producto.h"
#include "..\Models\Usuario.h"
#include "..\Servicios\Conexion.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaDepositoABM.h"
#include "..\Vistas\VistaFormulario.h"

namespace Controladores {
    ref class ControladorAdmin;
    ref class ControladorLogin;
}

using namespace Models;
using namespace Servicios;
using namespace Vistas;
using namespace MySql::Data::MySqlClient;

namespace Controladores {
    public ref class ControladorDepositoABM {
    private:
        Conexion^ c;
        Usuario^ usuario;
        VentanaPrincipal^ ventanaPrincipal;
        VistaDepositoABM^ vista;
        int filtroActual;

        void volverButton_Click(Object^ sender, EventArgs^ e);

        Producto^ mapearProducto(MySqlDataReader^ rs) {
            auto p = gcnew Producto();
            p->Id = safe_cast<int>(rs["id"]);
            p->Habilitado = safe_cast<int>(rs["habilitado"]);
            p->Descripcion = rs["descripcion"]->ToString();
            p->Precio = safe_cast<int>(rs["precio"]);
            p->Stock = safe_cast<int>(rs["stock"]);
            return p;
        }

        void poblarTabla() {
            vista->tableProductos->Columns->Clear();
            vista->tableProductos->Columns->Add(L"ID", L"ID");
            vista->tableProductos->Columns->Add(L"Descripcion", L"Descripcion");
            vista->tableProductos->Columns->Add(L"Precio", L"Precio");
            vista->tableProductos->Columns->Add(L"Stock", L"Stock");
            vista->tableProductos->Columns->Add(L"Habilitado", L"Habilitado");
            vista->tableProductos->Columns[4]->Visible = false;

            vista->tableProductos->Rows->Clear();
            auto productos = obtenerProductosPorHabilitado(filtroActual);
            for each (Producto^ p in productos) {
                vista->tableProductos->Rows->Add(p->Id, p->Descripcion, p->Precio, p->Stock, p->Habilitado);
            }
        }

        void comboBoxChanged(Object^ sender, EventArgs^ e) {
            filtroActual = vista->comboBoxFlitro->SelectedIndex == 0 ? 1 : 0;
            poblarTabla();
            vista->deshabilitarButton->Text = filtroActual == 1 ? L"Deshabilitar" : L"Habilitar";
        }

        void buscarButton_Click(Object^ sender, EventArgs^ e) {
            String^ texto = this->vista->textFieldID->Text->Trim();
            if (String::IsNullOrEmpty(texto)) { this->poblarTabla(); return; }
            auto resultados = this->buscarProducto(texto, this->filtroActual);
            if (resultados->Count > 0) {
                this->vista->tableProductos->Rows->Clear();
                for each (Producto^ p in resultados) {
                    this->vista->tableProductos->Rows->Add(p->Id, p->Descripcion, p->Precio, p->Stock, p->Habilitado);
                }
            }
        }

        void agregarButton_Click(Object^ sender, EventArgs^ e) {
            auto valores = VistaFormulario::mostrarDialogo(L"Nuevo Producto",
                gcnew VistaFormulario::Campo(L"Descripcion:"),
                gcnew VistaFormulario::Campo(L"Precio:"),
                gcnew VistaFormulario::Campo(L"Stock:")
            );
            if (valores != nullptr) {
                try {
                    int precio = Int32::Parse(valores[L"Precio:"]);
                    int stock = Int32::Parse(valores[L"Stock:"]);
                    if (this->agregarProducto(valores[L"Descripcion:"], precio, stock) > -1) this->poblarTabla();
                }
                catch (FormatException^) { MessageBox::Show(L"Precio y Stock deben ser numeros enteros"); }
            }
        }

        void modificarButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tableProductos->SelectedRows->Count == 0) { MessageBox::Show(L"Seleccione un producto de la tabla"); return; }
            auto fila = this->vista->tableProductos->SelectedRows[0];
            int idProducto = safe_cast<int>(fila->Cells[0]->Value);
            auto valores = VistaFormulario::mostrarDialogo(L"Modificar Producto",
                gcnew VistaFormulario::Campo(L"Descripcion:", fila->Cells[1]->Value->ToString()),
                gcnew VistaFormulario::Campo(L"Precio:", fila->Cells[2]->Value->ToString()),
                gcnew VistaFormulario::Campo(L"Stock:", fila->Cells[3]->Value->ToString())
            );
            if (valores != nullptr) {
                try {
                    if (this->modificarProducto(idProducto, valores[L"Descripcion:"], Int32::Parse(valores[L"Precio:"]), Int32::Parse(valores[L"Stock:"]))) this->poblarTabla();
                }
                catch (FormatException^) { MessageBox::Show(L"Precio y Stock deben ser numeros enteros"); }
            }
        }

        void deshabilitarButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tableProductos->SelectedRows->Count == 0) { MessageBox::Show(L"Seleccione un producto de la tabla"); return; }
            auto fila = this->vista->tableProductos->SelectedRows[0];
            int idProducto = safe_cast<int>(fila->Cells[0]->Value);
            int habilitadoActual = safe_cast<int>(fila->Cells[4]->Value);
            String^ nuevoEstado = habilitadoActual == 1 ? L"deshabilitar" : L"habilitar";
            auto result = MessageBox::Show(L"?Esta seguro de " + nuevoEstado + L" el producto \"" + fila->Cells[1]->Value->ToString() + L"\"?",
                nuevoEstado == L"deshabilitar" ? L"Deshabilitar Producto" : L"Habilitar Producto", MessageBoxButtons::YesNo);
            if (result == DialogResult::Yes) { if (this->toggleHabilitadoProducto(idProducto)) this->poblarTabla(); }
        }

    public:
        ControladorDepositoABM() : c(gcnew Conexion()), filtroActual(1) {}

        ControladorDepositoABM(Usuario^ usuario, VentanaPrincipal^ ventanaPrincipal) : c(gcnew Conexion()), filtroActual(1) {
            this->usuario = usuario;
            this->ventanaPrincipal = ventanaPrincipal;
            vista = gcnew VistaDepositoABM();
            ventanaPrincipal->setVista(vista->panelDepositoABM);

            poblarTabla();
            vista->comboBoxFlitro->SelectedIndexChanged += gcnew EventHandler(this, &ControladorDepositoABM::comboBoxChanged);

            vista->buscarButton->Click += gcnew EventHandler(this, &ControladorDepositoABM::buscarButton_Click);
            vista->agregarButton->Click += gcnew EventHandler(this, &ControladorDepositoABM::agregarButton_Click);
            vista->modificarButton->Click += gcnew EventHandler(this, &ControladorDepositoABM::modificarButton_Click);
            vista->deshabilitarButton->Click += gcnew EventHandler(this, &ControladorDepositoABM::deshabilitarButton_Click);
            vista->volverButton->Click += gcnew EventHandler(this, &ControladorDepositoABM::volverButton_Click);
        }

        List<Producto^>^ obtenerProductosPorHabilitado(int habilitado) {
            auto productos = gcnew List<Producto^>();
            c->conectar();
            String^ sql = "SELECT id, descripcion, precio, stock, habilitado FROM productos WHERE habilitado = ?habilitado";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?habilitado", habilitado);
            auto rs = cmd->ExecuteReader();
            while (rs->Read()) productos->Add(mapearProducto(rs));
            rs->Close();
            return productos;
        }

        List<Producto^>^ buscarProducto(String^ texto, int habilitado) {
            auto productos = gcnew List<Producto^>();
            c->conectar();
            MySqlCommand^ cmd;
            if (System::Text::RegularExpressions::Regex::IsMatch(texto, L"\\d+")) {
                cmd = gcnew MySqlCommand("SELECT id, descripcion, precio, stock, habilitado FROM productos WHERE id = ?id AND habilitado = ?habilitado", c->con);
                cmd->Parameters->AddWithValue("?id", Int32::Parse(texto));
            }
            else {
                cmd = gcnew MySqlCommand("SELECT id, descripcion, precio, stock, habilitado FROM productos WHERE descripcion LIKE ?desc AND habilitado = ?habilitado", c->con);
                cmd->Parameters->AddWithValue("?desc", L"%" + texto + L"%");
            }
            cmd->Parameters->AddWithValue("?habilitado", habilitado);
            auto rs = cmd->ExecuteReader();
            while (rs->Read()) productos->Add(mapearProducto(rs));
            rs->Close();
            if (productos->Count == 0) MessageBox::Show(L"No se encontraron productos con ese criterio");
            return productos;
        }

        int agregarProducto(String^ descripcion, int precio, int stock) {
            c->conectar();
            auto cmd = gcnew MySqlCommand("INSERT INTO productos(descripcion, precio, stock) VALUES(?descripcion, ?precio, ?stock)", c->con);
            cmd->Parameters->AddWithValue("?descripcion", descripcion);
            cmd->Parameters->AddWithValue("?precio", precio);
            cmd->Parameters->AddWithValue("?stock", stock);
            cmd->ExecuteNonQuery();
            int id = safe_cast<int>(cmd->LastInsertedId);
            MessageBox::Show(L"Producto agregado exitosamente");
            return id;
        }

        bool modificarProducto(int id, String^ descripcion, int precio, int stock) {
            c->conectar();
            auto cmd = gcnew MySqlCommand("UPDATE productos SET descripcion=?descripcion, precio=?precio, stock=?stock WHERE id=?id", c->con);
            cmd->Parameters->AddWithValue("?descripcion", descripcion);
            cmd->Parameters->AddWithValue("?precio", precio);
            cmd->Parameters->AddWithValue("?stock", stock);
            cmd->Parameters->AddWithValue("?id", id);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Producto modificado exitosamente");
            return true;
        }

        bool toggleHabilitadoProducto(int id) {
            c->conectar();
            auto cmd = gcnew MySqlCommand("UPDATE productos SET habilitado = CASE WHEN habilitado = 1 THEN 0 ELSE 1 END WHERE id = ?id", c->con);
            cmd->Parameters->AddWithValue("?id", id);
            cmd->ExecuteNonQuery();
            MessageBox::Show(L"Estado cambiado exitosamente");
            return true;
        }
    };
}
