#pragma once
#include "..\Filtros\FiltroAlfanumerico.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Filtros;

namespace Vistas {
    public ref class VistaDepositoABM {
    public:
        Panel^ panelDepositoABM;
        DataGridView^ tableProductos;
        TextBox^ textFieldID;
        ComboBox^ comboBoxFlitro;
        Button^ buscarButton;
        Button^ agregarButton;
        Button^ modificarButton;
        Button^ deshabilitarButton;
        Button^ volverButton;

        VistaDepositoABM() {
            auto azul = Color::LightSkyBlue;

            panelDepositoABM = gcnew Panel();
            panelDepositoABM->Size = System::Drawing::Size(800, 600);

            comboBoxFlitro = gcnew ComboBox();
            comboBoxFlitro->Items->Add(L"Habilitados");
            comboBoxFlitro->Items->Add(L"Deshabilitados");
            comboBoxFlitro->DropDownStyle = ComboBoxStyle::DropDownList;
            comboBoxFlitro->Location = Point(15, 15);
            comboBoxFlitro->Size = System::Drawing::Size(120, 25);
            panelDepositoABM->Controls->Add(comboBoxFlitro);
            comboBoxFlitro->SelectedIndex = 0;

            auto lblBuscar = gcnew Label();
            lblBuscar->Text = L"ID o Descripcion:";
            lblBuscar->Location = Point(145, 15);
            lblBuscar->Size = System::Drawing::Size(115, 25);
            lblBuscar->TextAlign = ContentAlignment::MiddleLeft;
            panelDepositoABM->Controls->Add(lblBuscar);

            textFieldID = gcnew TextBox();
            textFieldID->Location = Point(265, 15);
            textFieldID->Size = System::Drawing::Size(100, 25);
            panelDepositoABM->Controls->Add(textFieldID);
            FiltroAlfanumerico::Aplicar(textFieldID);

            buscarButton = gcnew Button();
            buscarButton->Text = L"Buscar";
            buscarButton->Location = Point(375, 15);
            buscarButton->Size = System::Drawing::Size(80, 25);
            buscarButton->BackColor = azul;
            panelDepositoABM->Controls->Add(buscarButton);

            agregarButton = gcnew Button();
            agregarButton->Text = L"Agregar";
            agregarButton->Location = Point(15, 55);
            agregarButton->Size = System::Drawing::Size(90, 30);
            agregarButton->BackColor = azul;
            panelDepositoABM->Controls->Add(agregarButton);

            modificarButton = gcnew Button();
            modificarButton->Text = L"Modificar";
            modificarButton->Location = Point(115, 55);
            modificarButton->Size = System::Drawing::Size(90, 30);
            modificarButton->BackColor = azul;
            panelDepositoABM->Controls->Add(modificarButton);

            deshabilitarButton = gcnew Button();
            deshabilitarButton->Text = L"Deshabilitar";
            deshabilitarButton->Location = Point(215, 55);
            deshabilitarButton->Size = System::Drawing::Size(90, 30);
            deshabilitarButton->BackColor = azul;
            panelDepositoABM->Controls->Add(deshabilitarButton);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, 55);
            volverButton->Size = System::Drawing::Size(100, 30);
            volverButton->BackColor = Color::Gainsboro;
            panelDepositoABM->Controls->Add(volverButton);

            tableProductos = gcnew DataGridView();
            tableProductos->Location = Point(15, 100);
            tableProductos->Size = System::Drawing::Size(770, 480);
            tableProductos->AllowUserToAddRows = false;
            tableProductos->AllowUserToDeleteRows = false;
            tableProductos->ReadOnly = true;
            tableProductos->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tableProductos->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelDepositoABM->Controls->Add(tableProductos);
        }
    };
}
