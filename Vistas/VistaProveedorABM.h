#pragma once
#include "..\Filtros\FiltroNumerico.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Filtros;

namespace Vistas {
    public ref class VistaProveedorABM {
    public:
        Panel^ panelProveedorABM;
        DataGridView^ tablaProveedores;
        TextBox^ textFieldID;
        ComboBox^ comboBoxFiltroHabilitado;
        Button^ buscarButton;
        Button^ agregarButton;
        Button^ modificarButton;
        Button^ deshabilitarButton;
        Button^ volverButton;

        VistaProveedorABM() {
            auto azul = Color::LightSkyBlue;

            panelProveedorABM = gcnew Panel();
            panelProveedorABM->Size = System::Drawing::Size(800, 600);

            comboBoxFiltroHabilitado = gcnew ComboBox();
            comboBoxFiltroHabilitado->Items->Add(L"Habilitados");
            comboBoxFiltroHabilitado->Items->Add(L"Deshabilitados");
            comboBoxFiltroHabilitado->DropDownStyle = ComboBoxStyle::DropDownList;
            comboBoxFiltroHabilitado->Location = Point(15, 15);
            comboBoxFiltroHabilitado->Size = System::Drawing::Size(120, 25);
            panelProveedorABM->Controls->Add(comboBoxFiltroHabilitado);
            comboBoxFiltroHabilitado->SelectedIndex = 0;

            auto lblBuscar = gcnew Label();
            lblBuscar->Text = L"ID Proveedor:";
            lblBuscar->Location = Point(145, 15);
            lblBuscar->Size = System::Drawing::Size(80, 25);
            lblBuscar->TextAlign = ContentAlignment::MiddleLeft;
            panelProveedorABM->Controls->Add(lblBuscar);

            textFieldID = gcnew TextBox();
            textFieldID->Location = Point(230, 15);
            textFieldID->Size = System::Drawing::Size(100, 25);
            panelProveedorABM->Controls->Add(textFieldID);
            FiltroNumerico::Aplicar(textFieldID);

            buscarButton = gcnew Button();
            buscarButton->Text = L"Buscar";
            buscarButton->Location = Point(340, 15);
            buscarButton->Size = System::Drawing::Size(80, 25);
            buscarButton->BackColor = azul;
            panelProveedorABM->Controls->Add(buscarButton);

            agregarButton = gcnew Button();
            agregarButton->Text = L"Agregar";
            agregarButton->Location = Point(15, 55);
            agregarButton->Size = System::Drawing::Size(90, 30);
            agregarButton->BackColor = azul;
            panelProveedorABM->Controls->Add(agregarButton);

            modificarButton = gcnew Button();
            modificarButton->Text = L"Modificar";
            modificarButton->Location = Point(115, 55);
            modificarButton->Size = System::Drawing::Size(90, 30);
            modificarButton->BackColor = azul;
            panelProveedorABM->Controls->Add(modificarButton);

            deshabilitarButton = gcnew Button();
            deshabilitarButton->Text = L"Deshabilitar";
            deshabilitarButton->Location = Point(215, 55);
            deshabilitarButton->Size = System::Drawing::Size(90, 30);
            deshabilitarButton->BackColor = azul;
            panelProveedorABM->Controls->Add(deshabilitarButton);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, 55);
            volverButton->Size = System::Drawing::Size(100, 30);
            volverButton->BackColor = Color::Gainsboro;
            panelProveedorABM->Controls->Add(volverButton);

            tablaProveedores = gcnew DataGridView();
            tablaProveedores->Location = Point(15, 100);
            tablaProveedores->Size = System::Drawing::Size(770, 480);
            tablaProveedores->AllowUserToAddRows = false;
            tablaProveedores->AllowUserToDeleteRows = false;
            tablaProveedores->ReadOnly = true;
            tablaProveedores->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tablaProveedores->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelProveedorABM->Controls->Add(tablaProveedores);
        }
    };
}
