#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace Vistas {
    public ref class VistaFormulario {
    public:
        ref class Campo {
        public:
            String^ Etiqueta;
            bool EsPassword;
            array<String^>^ Opciones;
            String^ ValorInicial;

            Campo(String^ etiqueta) : Etiqueta(etiqueta), EsPassword(false), Opciones(nullptr), ValorInicial(nullptr) {}
            Campo(String^ etiqueta, bool esPassword) : Etiqueta(etiqueta), EsPassword(esPassword), Opciones(nullptr), ValorInicial(nullptr) {}
            Campo(String^ etiqueta, String^ valorInicial) : Etiqueta(etiqueta), EsPassword(false), Opciones(nullptr), ValorInicial(valorInicial) {}
            Campo(String^ etiqueta, bool esPassword, String^ valorInicial) : Etiqueta(etiqueta), EsPassword(esPassword), Opciones(nullptr), ValorInicial(valorInicial) {}
            Campo(String^ etiqueta, array<String^>^ opciones) : Etiqueta(etiqueta), EsPassword(false), Opciones(opciones), ValorInicial(nullptr) {}
            Campo(String^ etiqueta, array<String^>^ opciones, String^ valorInicial) : Etiqueta(etiqueta), EsPassword(false), Opciones(opciones), ValorInicial(valorInicial) {}
        };

        static void MostrarPasswordChanged(Object^ sender, EventArgs^ e) {
            bool show = ((CheckBox^)sender)->Checked;
            auto fields = (List<TextBox^>^)((CheckBox^)sender)->Tag;
            for each (TextBox^ tb in fields) {
                tb->UseSystemPasswordChar = !show;
            }
        }

        static Dictionary<String^, String^>^ mostrarDialogo(String^ titulo, ... array<Campo^>^ campos) {
            auto form = gcnew Form();
            form->Text = titulo;
            form->Size = System::Drawing::Size(350, campos->Length * 35 + 100);
            form->FormBorderStyle = FormBorderStyle::FixedDialog;
            form->StartPosition = FormStartPosition::CenterParent;
            form->MinimizeBox = false;
            form->MaximizeBox = false;
            form->ShowInTaskbar = false;

            auto passwordFields = gcnew List<TextBox^>();

            for (int i = 0; i < campos->Length; i++) {
                Campo^ c = campos[i];

                auto lbl = gcnew Label();
                lbl->Text = c->Etiqueta;
                lbl->Location = Point(10, 10 + i * 35);
                lbl->Size = System::Drawing::Size(100, 25);
                form->Controls->Add(lbl);

                if (c->Opciones != nullptr) {
                    auto cb = gcnew ComboBox();
                    cb->Items->AddRange(c->Opciones);
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

            auto btnOk = gcnew Button();
            btnOk->Text = L"Aceptar";
            btnOk->DialogResult = DialogResult::OK;
            btnOk->Location = Point(120, 10 + campos->Length * 35 + (passwordFields->Count > 0 ? 30 : 0));
            btnOk->Size = System::Drawing::Size(90, 30);
            form->Controls->Add(btnOk);

            auto btnCancel = gcnew Button();
            btnCancel->Text = L"Cancelar";
            btnCancel->DialogResult = DialogResult::Cancel;
            btnCancel->Location = Point(220, 10 + campos->Length * 35 + (passwordFields->Count > 0 ? 30 : 0));
            btnCancel->Size = System::Drawing::Size(90, 30);
            form->Controls->Add(btnCancel);

            form->AcceptButton = btnOk;
            form->CancelButton = btnCancel;

            if (form->ShowDialog() != DialogResult::OK) return nullptr;

            auto resultado = gcnew Dictionary<String^, String^>();
            int controlIndex = 0;
            for (int i = 0; i < campos->Length; i++) {
                Campo^ c = campos[i];
                int idx = 1 + i; // first control is label, but we access by index
                auto comp = form->Controls[i * 2 + 1]; // every other control
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
