#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Vistas {
    public ref class VistaDetallesFactura {
    public:
        Panel^ panelDetallesFactura;
        Label^ labelTitulo;
        TextBox^ textFieldNumeroFactura;
        TextBox^ textFieldFecha;
        TextBox^ textFieldNombreCliente;
        TextBox^ textFieldApellidoCliente;
        TextBox^ textFieldDNICliente;
        TextBox^ textFieldDireccionCliente;
        TextBox^ textFieldNombreVendedor;
        TextBox^ textFieldApellidoVendedor;
        TextBox^ textFieldTotal;
        TextBox^ textFieldIDCliente;
        TextBox^ textFieldIDVendedor;
        TextBox^ textFieldDescontado;
        TextBox^ textFieldPorcentajeDescuento;
        TextBox^ textFieldSubtotal;
        DataGridView^ tableDetalles;
        Button^ volverButton;

        VistaDetallesFactura() {
            panelDetallesFactura = gcnew Panel();
            panelDetallesFactura->Size = System::Drawing::Size(800, 600);

            labelTitulo = gcnew Label();
            labelTitulo->Text = L"Detalles de Factura";
            labelTitulo->Font = gcnew System::Drawing::Font(L"Arial", 14);
            labelTitulo->Location = Point(250, 10);
            labelTitulo->Size = System::Drawing::Size(300, 30);
            panelDetallesFactura->Controls->Add(labelTitulo);

            array<String^>^ lbls = { L"Nro Factura:", L"Fecha:", L"Cliente:", L"Apellido:", L"DNI:", L"Direccion:", L"Vendedor:", L"Apellido V:", L"ID Cliente:", L"ID Vendedor:" };
            array<TextBox^>^ tbs = gcnew array<TextBox^>(10);
            int y = 50;
            for (int i = 0; i < 5; i++) {
                auto lbl1 = gcnew Label();
                lbl1->Text = lbls[i];
                lbl1->Location = Point(20, y);
                lbl1->Size = System::Drawing::Size(80, 20);
                panelDetallesFactura->Controls->Add(lbl1);

                tbs[i] = gcnew TextBox();
                tbs[i]->Location = Point(100, y);
                tbs[i]->Size = System::Drawing::Size(120, 20);
                tbs[i]->ReadOnly = true;
                panelDetallesFactura->Controls->Add(tbs[i]);

                auto lbl2 = gcnew Label();
                lbl2->Text = lbls[i + 5];
                lbl2->Location = Point(240, y);
                lbl2->Size = System::Drawing::Size(80, 20);
                panelDetallesFactura->Controls->Add(lbl2);

                tbs[i + 5] = gcnew TextBox();
                tbs[i + 5]->Location = Point(320, y);
                tbs[i + 5]->Size = System::Drawing::Size(120, 20);
                tbs[i + 5]->ReadOnly = true;
                panelDetallesFactura->Controls->Add(tbs[i + 5]);
                y += 25;
            }

            textFieldNumeroFactura = tbs[0];
            textFieldFecha = tbs[1];
            textFieldNombreCliente = tbs[2];
            textFieldApellidoCliente = tbs[3];
            textFieldDNICliente = tbs[4];
            textFieldDireccionCliente = tbs[5];
            textFieldNombreVendedor = tbs[6];
            textFieldApellidoVendedor = tbs[7];
            textFieldIDCliente = tbs[8];
            textFieldIDVendedor = tbs[9];

            y += 10;
            array<String^>^ finLbls = { L"Subtotal:", L"Descuento:", L"Descontado:", L"Total:" };
            array<TextBox^>^ finTbs = gcnew array<TextBox^>(4);
            for (int i = 0; i < 4; i++) {
                auto lbl = gcnew Label();
                lbl->Text = finLbls[i];
                lbl->Location = Point(20 + (i % 2) * 220, y);
                lbl->Size = System::Drawing::Size(80, 20);
                panelDetallesFactura->Controls->Add(lbl);

                finTbs[i] = gcnew TextBox();
                finTbs[i]->Location = Point(100 + (i % 2) * 220, y);
                finTbs[i]->Size = System::Drawing::Size(100, 20);
                finTbs[i]->ReadOnly = true;
                panelDetallesFactura->Controls->Add(finTbs[i]);

                if (i % 2 == 1) y += 25;
            }
            textFieldSubtotal = finTbs[0];
            textFieldPorcentajeDescuento = finTbs[1];
            textFieldDescontado = finTbs[2];
            textFieldTotal = finTbs[3];

            tableDetalles = gcnew DataGridView();
            tableDetalles->Location = Point(20, y + 10);
            tableDetalles->Size = System::Drawing::Size(740, 200);
            tableDetalles->AllowUserToAddRows = false;
            tableDetalles->AllowUserToDeleteRows = false;
            tableDetalles->ReadOnly = true;
            tableDetalles->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelDetallesFactura->Controls->Add(tableDetalles);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, y + 220);
            volverButton->Size = System::Drawing::Size(100, 30);
            panelDetallesFactura->Controls->Add(volverButton);
        }
    };
}
