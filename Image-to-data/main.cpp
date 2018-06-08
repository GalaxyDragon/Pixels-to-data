#include <QApplication>
#include <QtWidgets>
#include <QObject>
#include "cnt.h"
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName( QString("Pixels to data") );



    QGroupBox* radio = new QGroupBox("Формат вывода");
    QRadioButton* hex = new QRadioButton("hex");
    QRadioButton* bin = new QRadioButton("binary");
    bin->setChecked(true);
    QHBoxLayout* data_form = new QHBoxLayout;
    data_form->addWidget(hex);data_form->addWidget(bin);
    radio->setLayout(data_form);


    QSpinBox* hi = new QSpinBox;
    QSpinBox* we = new QSpinBox;
    QSpinBox* cell = new QSpinBox;
    QTableWidget* tab = new QTableWidget(8,8);
    QTextEdit* res = new QTextEdit;
    QPushButton* copy = new QPushButton("Копировать");
    copy->resize(QSize(100,20));
    copy->setMaximumWidth(100);
    res->setReadOnly(true);
    QPushButton* top_apply = new QPushButton("Применить");
    QPushButton* cell_apply = new QPushButton("Применить");
    QWidget w;
    QPushButton* count = new QPushButton("Вычислить");
    count->resize(100,30);
    count->setMaximumWidth(100);
    res->setMaximumHeight(20);
    QHBoxLayout* top_cell =new QHBoxLayout;
    QVBoxLayout* mn = new QVBoxLayout;
    QHBoxLayout* top = new QHBoxLayout;
    hi->setRange(1,128);
    we->setRange(1,128);
    cell->setRange(1,100); cell->setSuffix(" px"); cell->setValue(50);
    top_cell->addWidget(new QLabel("Размер ячейки"));
    top_cell->addWidget(cell);top_cell->addWidget(cell_apply);top_cell->addWidget(radio);top_cell->addStretch(1);
    hi->resize(QSize(70,20));we->resize(QSize(70,20));top_apply->resize(100,20);cell_apply->resize(100,20);
    hi->setMaximumWidth(70);we->setMaximumWidth(70);top_apply->setMaximumWidth(100);cell_apply->setMaximumWidth(100);
    hi->setButtonSymbols(QSpinBox::PlusMinus); we->setButtonSymbols(QSpinBox::PlusMinus);cell->setButtonSymbols(QSpinBox::PlusMinus);
    top->addWidget(hi);top->addWidget(new QLabel("x"));top->addWidget(we);top->addWidget(top_apply);top->addStretch(1);
    top->setSpacing(10);

    cnt* applyer = new cnt();
    applyer->tab = tab;
    applyer->hi = hi;
    applyer->we = we;
    applyer->mn = &w;
    applyer->cell = cell;
    applyer->hex = hex;
    applyer->bin = bin;
    applyer->text = res;
    QObject::connect(top_apply, SIGNAL(clicked()), applyer, SLOT(table_resize()));
    QObject::connect(cell_apply, SIGNAL(clicked()),applyer,SLOT(cell_resize()));
    QObject::connect(count, SIGNAL(clicked()),applyer,SLOT(count()));
    QObject::connect(copy,SIGNAL(clicked()),applyer,SLOT(copy()));
    for(int i=0; i<8;i++){
        for(int j=0; j<8;j++){
            QPushButton* butt = new QPushButton();
            butt->setStyleSheet("QPushButton:checked { background-color: rgb(0,0,0);}");
            butt->setFlat(true);
            butt->setChecked(false);
            butt->setCheckable(true);
            tab->setCellWidget(i,j,butt);
            tab->horizontalHeader()->setDefaultSectionSize(50);
            tab->verticalHeader()->setDefaultSectionSize(50);
        }
    }
    QHBoxLayout* results = new QHBoxLayout;
    results->addWidget(res);results->addWidget(copy);
    mn->addWidget(new QLabel("Размер таблицы"));
    mn->addLayout(top);
    mn->addLayout(top_cell);
    mn->addWidget(tab);
    mn->addWidget(count);
    mn->addLayout(results);
    w.setLayout(mn);
    w.resize(800,600);
    w.show();
    return app.exec();
}
