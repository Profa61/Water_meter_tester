from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice
#import time


# https://stackoverflow.com/questions/35932660/qcombobox-click-event обновление по клику
app = QtWidgets.QApplication([])
ui = uic.loadUi("design.ui")
ui.setWindowTitle("Test Betar")

serial = QSerialPort()
serial.setBaudRate(9600)


# прочитать порт
def onRead():

    if not serial.canReadLine(): return
    rx = serial.readLine()
    data = str(rx, 'utf-8').strip().split(',')  # подрезать и разбить по запятым
    print(data)
    if data[0] != '1':
        data[0] = '0'
    # парсинг
    if data[0] == '1':
        for i in data:
            print(i)


        #print(data[1])
        ui.literBox.setValue(int(data[1]))
        #time.sleep(2)
        ui.speedS.setValue(int(data[2]))
        del data


    # if data[0] == '2':
    #     print(data[1])
    #     ui.speedS.setValue(int(data[1]))




# открыть порт
def onOpen():
    serial.setPortName(ui.comL.currentText())
    serial.open(QIODevice.ReadWrite)


# отправить массив int данных
def serialSend(data):
    # короткий способ перевести int data в строки, соединить через запятую и прибавить \n
    txs = ','.join(map(str, data)) # + '\n'
    serial.write(txs.encode())  # преобразовать в байты и отправить


# закрыть порт
def onClose():
    serial.close()


# обновить список портов
def updateList():
    portList = []
    ports = QSerialPortInfo().availablePorts()
    for port in ports:portList.append(port.portName())
    ui.comL.clear()
    ui.comL.addItems(portList)

def onstart():
    #ui.literBox.setValue(int(counter))
    #serial.write((bytes(f"t{ui.literBox.value()}", encoding='ascii')))
    serial.write((bytes("a0", encoding='ascii')))


def onstop():
    serial.write((bytes("b0", encoding='ascii')))


def speedControl():
    serial.write((bytes(f"s{ui.speedS.value()}", encoding='ascii')))
    ui.lcdCounter.display(ui.speedS.value())
    #print(f"s{ui.speedS.value()}")


def literControl():
    #x = ui.spinBox.QSpinBox.setValue()
    serial.write((bytes(f"t{ui.literBox.value()}", encoding='ascii')))
    #print(f"t{ui.literBox.value()}")


def presetControl():
    if ui.presetB.isChecked():
        serial.write((bytes("p1", encoding='ascii')))

    else:
       serial.write((bytes("p0", encoding='ascii')))


def rotateControl():
    if ui.rotateB.isChecked():
        serial.write((bytes("c1", encoding='ascii')))
    else:
        serial.write((bytes("c0", encoding='ascii')))


def countClear():
    serial.write((bytes("r0", encoding='ascii')))


def install():
    if ui.instalA.isChecked():
        ui.spinA.setEnabled(True)
        ui.spinA1.setEnabled(True)
        ui.spinA2.setEnabled(True)
        ui.spinB.setEnabled(True)
        ui.spinB1.setEnabled(True)
        ui.spinB2.setEnabled(True)
        ui.spinC.setEnabled(True)
        ui.spinC1.setEnabled(True)
        ui.spinC2.setEnabled(True)
    else:
        ui.spinA.setEnabled(False)
        ui.spinA1.setEnabled(False)
        ui.spinA2.setEnabled(False)
        ui.spinB.setEnabled(False)
        ui.spinB1.setEnabled(False)
        ui.spinB2.setEnabled(False)
        ui.spinC.setEnabled(False)
        ui.spinC1.setEnabled(False)
        ui.spinC2.setEnabled(False)

def setting():
   # serial.write((bytes("k", encoding='ascii')))
   serialSend("k")






# пошла программа
#serial.readyRead.connect(onRead)
ui.openB.clicked.connect(onOpen)
ui.closeB.clicked.connect(onClose)
ui.startB.clicked.connect(onstart)
ui.stopB.clicked.connect(onstop)
ui.speedS.valueChanged.connect(speedControl)
ui.literB.clicked.connect(literControl)
ui.presetB.toggled.connect(presetControl)
ui.rotateB.toggled.connect(rotateControl)
ui.clearCount.clicked.connect(countClear)
ui.instalA.toggled.connect(install)
ui.settingsB.clicked.connect(setting)


updateList()

ui.show()
app.exec()


