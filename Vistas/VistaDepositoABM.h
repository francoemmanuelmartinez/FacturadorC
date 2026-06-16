#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

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
            panelDepositoABM = gcnew Panel();
            panelDepositoABM->Size = System::Drawing::Size(800, 600);

            auto lblTitulo = gcnew Label();
            lblTitulo->Text = L"Gestion de Deposito";
            lblTitulo->Font = gcnew System::Drawing::Font(L"Arial", 14);
            lblTitulo->Location = Point(250, 20);
            lblTitulo->Size = System::Drawing::Size(250, 30);
            panelDepositoABM->Controls->Add(lblTitulo);

            auto lblFiltro = gcnew Label();
            lblFiltro->Text = L"Filtro:";
            lblFiltro->Location = Point(20, 60);
            lblFiltro->Size = System::Drawing::Size(50, 20);
            panelDepositoABM->Controls->Add(lblFiltro);

            comboBoxFlitro = gcnew ComboBox();
            comboBoxFlitro->Location = Point(70, 60);
            comboBoxFlitro->Size = System::Drawing::Size(120, 20);
            comboBoxFlitro->Items->Add(L"Habilitados");
            comboBoxFlitro->Items->Add(L"Deshabilitados");
            panelDepositoABM->Controls->Add(comboBoxFlitro);

            auto lblBuscar = gcnew Label();
            lblBuscar->Text = L"ID/Desc:";
            lblBuscar->Location = Point(220, 60);
            lblBuscar->Size = System::Drawing::Size(60, 20);
            panelDepositoABM->Controls->Add(lblBuscar);

            textFieldID = gcnew TextBox();
            textFieldID->Location = Point(280, 60);
            textFieldID->Size = System::Drawing::Size(120, 20);
            panelDepositoABM->Controls->Add(textFieldID);

            buscarButton = gcnew Button();
            buscarButton->Text = L"Buscar";
            buscarButton->Location = Point(410, 58);
            buscarButton->Size = System::Drawing::Size(80, 25);
            panelDepositoABM->Controls->Add(buscarButton);

            tableProductos = gcnew DataGridView();
            tableProductos->Location = Point(20, 100);
            tableProductos->Size = System::Drawing::Size(740, 350);
            tableProductos->AllowUserToAddRows = false;
            tableProductos->AllowUserToDeleteRows = false;
            tableProductos->ReadOnly = true;
            tableProductos->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tableProductos->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelDepositoABM->Controls->Add(tableProductos);

            agregarButton = gcnew Button();
            agregarButton->Text = L"Agregar";
            agregarButton->Location = Point(20, 470);
            agregarButton->Size = System::Drawing::Size(100, 30);
            panelDepositoABM->Controls->Add(agregarButton);

            modificarButton = gcnew Button();
            modificarButton->Text = L"Modificar";
            modificarButton->Location = Point(130, 470);
            modificarButton->Size = System::Drawing::Size(100, 30);
            panelDepositoABM->Controls->Add(modificarButton);

            deshabilitarButton = gcnew Button();
            deshabilitarButton->Text = L"Deshabilitar";
            deshabilitarButton->Location = Point(240, 470);
            deshabilitarButton->Size = System::Drawing::Size(100, 30);
            panelDepositoABM->Controls->Add(deshabilitarButton);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, 470);
            volverButton->Size = System::Drawing::Size(100, 30);
            panelDepositoABM->Controls->Add(volverButton);
        }
    };
}
