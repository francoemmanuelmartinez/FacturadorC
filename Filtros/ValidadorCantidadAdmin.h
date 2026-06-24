#pragma once
#include "..\Servicios\Conexion.h"

using namespace System;
using namespace Servicios;
using namespace MySql::Data::MySqlClient;

namespace Filtros {
    public ref class ValidadorCantidadAdmin {
    public:
        static bool permitirDeshabilitar(int idUsuario) {
            try {
                auto c = gcnew Conexion();
                c->conectar();
                String^ sql = "SELECT COUNT(*) FROM usuarios WHERE rol = 'Administrador' AND habilitado = 1 AND id != ?id";
                auto cmd = gcnew MySqlCommand(sql, c->con);
                cmd->Parameters->AddWithValue("?id", idUsuario);
                int count = Convert::ToInt32(cmd->ExecuteScalar());
                if (count == 0) {
                    MessageBox::Show(L"No se puede deshabilitar al unico administrador habilitado");
                    return false;
                }
                return true;
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Error: " + ex->Message);
                return false;
            }
        }

        static bool permitirCambiarRol(int idUsuario) {
            try {
                auto c = gcnew Conexion();
                c->conectar();
                String^ sql = "SELECT COUNT(*) FROM usuarios WHERE rol = 'Administrador' AND habilitado = 1 AND id != ?id";
                auto cmd = gcnew MySqlCommand(sql, c->con);
                cmd->Parameters->AddWithValue("?id", idUsuario);
                int count = Convert::ToInt32(cmd->ExecuteScalar());
                if (count == 0) {
                    MessageBox::Show(L"No se puede cambiar el rol del unico administrador habilitado");
                    return false;
                }
                return true;
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Error: " + ex->Message);
                return false;
            }
        }
    };
}
