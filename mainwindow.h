#pragma once

#include "ui_mainwindow.h"
#include "enums.h"

#include <QMainWindow>
#include <functional>
#include <string>
#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private slots:
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_0_clicked();

    void on_btn_erase_clicked();
    void on_btn_plus_minus_clicked();
    void on_btn_res_clicked();
    void on_btn_clear_clicked();
    void on_btn_ms_clicked();
    void on_btn_mc_clicked();
    void on_bt_mr_clicked();
    void on_tb_extra_clicked();

    void on_btn_in_pow_clicked();
    void on_btn_division_clicked();
    void on_btn_multiply_clicked();
    void on_btn_subtract_clicked();
    void on_btn_addition_clicked();

    void on_cmb_controller_currentIndexChanged(int index);

private:
    Ui::MainWindow* ui;

    std::function<void(int key)> digit_callback_;
    std::function<void(Operation key)> operation_callback_;
    std::function<void(ControlKey key)> control_callback_;
    std::function<void(ControllerType controller)> controller_callback_;
};
