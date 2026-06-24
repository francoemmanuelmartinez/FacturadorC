#pragma once
#include "..\Filtros\FiltroNumerico.h"
#include "..\Filtros\FiltroTexto.h"
#include "..\Filtros\FiltroAlfanumerico.h"
#include "..\Filtros\FiltroPrecio.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace Filtros;

namespace Vistas {
    public ref class VistaFormulario {
    public:
        ref class Campo {
        public:
            String^ Etiqueta;
            bool EsPassword;
            array<String^>^ Opciones;
            String^ ValorInicial;
            String^ TipoFiltro;
            bool Requerido;

            Campo(String^ etiqueta) : Etiqueta(etiqueta), EsPassword(false), Opciones(nullptr), ValorInicial(nullptr), TipoFiltro(nullptr), Requerido(false) {}
            Campo(String^ etiqueta, bool esPassword) : Etiqueta(etiqueta), EsPassword(esPassword), Opciones(nullptr), ValorInicial(nullptr), TipoFiltro(nullptr), Requerido(false) {}
            Campo(String^ etiqueta, String^ valorInicial) : Etiqueta(etiqueta), EsPassword(false), Opciones(nullptr), ValorInicial(valorInicial), TipoFiltro(nullptr), Requerido(false) {}
            Campo(String^ etiqueta, bool esPassword, String^ valorInicial) : Etiqueta(etiqueta), EsPassword(esPassword), Opciones(nullptr), ValorInicial(valorInicial), TipoFiltro(nullptr), Requerido(false) {}
            Campo(String^ etiqueta, array<String^>^ opciones) : Etiqueta(etiqueta), EsPassword(false), Opciones(opciones), ValorInicial(nullptr), TipoFiltro(nullptr), Requerido(false) {}
            Campo(String^ etiqueta, array<String^>^ opciones, String^ valorInicial) : Etiqueta(etiqueta), EsPassword(false), Opciones(opciones), ValorInicial(valorInicial), TipoFiltro(nullptr), Requerido(false) {}

            Campo(String^ etiqueta, String^ valorInicial, String^ tipoFiltro) : Etiqueta(etiqueta), EsPassword(false), Opciones(nullptr), ValorInicial(valorInicial), TipoFiltro(tipoFiltro), Requerido(false) {}
            Campo(String^ etiqueta, String^ valorInicial, String^ tipoFiltro, bool requerido) : Etiqueta(etiqueta), EsPassword(false), Opciones(nullptr), ValorInicial(valorInicial), TipoFiltro(tipoFiltro), Requerido(requerido) {}
            Campo(String^ etiqueta, array<String^>^ opciones, bool requerido) : Etiqueta(etiqueta), EsPassword(false), Opciones(opciones), ValorInicial(nullptr), TipoFiltro(nullptr), Requerido(requerido) {}
            Campo(String^ etiqueta, array<String^>^ opciones, String^ valorInicial, bool requerido) : Etiqueta(etiqueta), EsPassword(false), Opciones(opciones), ValorInicial(valorInicial), TipoFiltro(nullptr), Requerido(requerido) {}
            Campo(String^ etiqueta, bool esPassword, bool requerido) : Etiqueta(etiqueta), EsPassword(esPassword), Opciones(nullptr), ValorInicial(nullptr), TipoFiltro(nullptr), Requerido(requerido) {}
            Campo(String^ etiqueta, bool esPassword, String^ valorInicial, bool requerido) : Etiqueta(etiqueta), EsPassword(esPassword), Opciones(nullptr), ValorInicial(valorInicial), TipoFiltro(nullptr), Requerido(requerido) {}
        };

        static void MostrarPasswordChanged(Object^ sender, EventArgs^ e) {
            bool show = ((CheckBox^)sender)->Checked;
            auto fields = (List<TextBox^>^)((CheckBox^)sender)->Tag;
            for each (TextBox^ tb in fields) {
                tb->UseSystemPasswordChar = !show;
            }
        }

        static void AplicarFiltro(TextBox^ tb, String^ tipoFiltro) {
            if (tipoFiltro == L"Texto") FiltroTexto::Aplicar(tb);
            else if (tipoFiltro == L"Numerico") FiltroNumerico::Aplicar(tb);
            else if (tipoFiltro == L"Alfanumerico") FiltroAlfanumerico::Aplicar(tb);
            else if (tipoFiltro == L"Precio") FiltroPrecio::Aplicar(tb);
        }

        static Dictionary<String^, String^>^ mostrarDialogo(String^ titulo, ... array<Campo^>^ campos) {
            auto form = gcnew Form();
            form->Text = titulo;
            form->Size = System::Drawing::Size(350, campos->Length * 35 + 140);
            form->FormBorderStyle = FormBorderStyle::FixedDialog;
            form->StartPosition = FormStartPosition::CenterParent;
            form->MinimizeBox = false;
            form->MaximizeBox = false;
            form->ShowInTaskbar = false;

            auto passwordFields = gcnew List<TextBox^>();

            for (int i = 0; i < campos->Length; i++) {
                Campo^ c = campos[i];

                auto lbl = gcnew Label();
                lbl->Text = c->Requerido ? c->Etiqueta + L" *" : c->Etiqueta;
                if (c->Requerido) lbl->ForeColor = Color::Red;
                lbl->Location = Point(10, 10 + i * 35);
                lbl->Size = System::Drawing::Size(100, 25);
                form->Controls->Add(lbl);

                if (c->Opciones != nullptr) {
                    auto cb = gcnew ComboBox();
                    cb->Items->AddRange(c->Opciones);
                    cb->DropDownStyle = ComboBoxStyle::DropDownList;
                    cb->Location = Point(120, 10 + i * 35);
                    cb->Size = System::Drawing::Size(200, 25);
                    if (c->ValorInicial != nullptr) cb->Text = c->ValorInicial;
                    if (c->ValorInicial == nullptr && c->Opciones->Length > 0) cb->SelectedIndex = 0;
                    form->Controls->Add(cb);
                }
                else if (c->EsPassword) {
                    auto pf = gcnew TextBox();
                    pf->UseSystemPasswordChar = true;
                    pf->Location = Point(120, 10 + i * 35);
                    pf->Size = System::Drawing::Size(200, 25);
                    if (c->ValorInicial != nullptr) pf->Text = c->ValorInicial;
                    form->Controls->Add(pf);
                    passwordFields->Add(pf);
                }
                else {
                    auto tf = gcnew TextBox();
                    tf->Location = Point(120, 10 + i * 35);
                    tf->Size = System::Drawing::Size(200, 25);
                    if (c->ValorInicial != nullptr) tf->Text = c->ValorInicial;
                    form->Controls->Add(tf);
                    if (c->TipoFiltro != nullptr) AplicarFiltro(tf, c->TipoFiltro);
                }
            }

            if (passwordFields->Count > 0) {
                auto chk = gcnew CheckBox();
                chk->Text = L"Mostrar contrasena";
                chk->Location = Point(120, 10 + campos->Length * 35);
                chk->Size = System::Drawing::Size(200, 25);
                chk->Tag = passwordFields;
                chk->CheckedChanged += gcnew EventHandler(&VistaFormulario::MostrarPasswordChanged);
                form->Controls->Add(chk);
            }

            auto azul = Color::LightSkyBlue;

            auto btnOk = gcnew Button();
            btnOk->Text = L"Aceptar";
            btnOk->DialogResult = DialogResult::OK;
            btnOk->Location = Point(120, 10 + campos->Length * 35 + (passwordFields->Count > 0 ? 30 : 0));
            btnOk->Size = System::Drawing::Size(90, 30);
            btnOk->BackColor = Color::LightGreen;
            form->Controls->Add(btnOk);

            auto btnCancel = gcnew Button();
            btnCancel->Text = L"Cancelar";
            btnCancel->DialogResult = DialogResult::Cancel;
            btnCancel->Location = Point(220, 10 + campos->Length * 35 + (passwordFields->Count > 0 ? 30 : 0));
            btnCancel->Size = System::Drawing::Size(90, 30);
            btnCancel->BackColor = Color::LightCoral;
            form->Controls->Add(btnCancel);

            auto lblReq = gcnew Label();
            lblReq->Text = L"* Campos requeridos";
            lblReq->ForeColor = Color::Red;
            lblReq->Location = Point(10, 10 + campos->Length * 35 + (passwordFields->Count > 0 ? 30 : 0) + 35);
            lblReq->Size = System::Drawing::Size(200, 20);
            form->Controls->Add(lblReq);

            form->AcceptButton = btnOk;
            form->CancelButton = btnCancel;

            if (form->ShowDialog() != DialogResult::OK) return nullptr;

            auto resultado = gcnew Dictionary<String^, String^>();
            for (int i = 0; i < campos->Length; i++) {
                Campo^ c = campos[i];
                auto comp = form->Controls[i * 2 + 1];
                if (comp->GetType() == TextBox::typeid) {
                    resultado[c->Etiqueta] = ((TextBox^)comp)->Text->Trim();
                }
                else if (comp->GetType() == ComboBox::typeid) {
                    auto cb = (ComboBox^)comp;
                    resultado[c->Etiqueta] = cb->SelectedItem != nullptr ? cb->SelectedItem->ToString()->Trim() : L"";
                }
            }
            return resultado;
        }
    };
}
