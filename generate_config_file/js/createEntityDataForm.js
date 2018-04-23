/*** Created by wangshaobo_ on 2017/8/3.*/
define(['js/createModel'], function (createModel) {
    'use strict';
    var dataFormArrayHistory = [];
    var dataFormArray = [],
        createDataFormArray=function(){
          this.dataFormArray=[];
            this.getDataFormArray=function(){
                return this.dataFormArray;
            }
        },
        createDataForm = function () {
            this.deviceDescription = new createDeviceDescription;
            this.IODescriptionArray = [];
            this.getDeviceDescription = function () {
                return this.deviceDescription;
            }
            this.getIODescriptionArray = function () {
                return this.IODescriptionArray;
            }
        },
        createDeviceDescription = function () {
            this.typeName = null;
            this.uid = null;
            this.devicePropertyArray = [];
            this.getTypeName = function () {
                return this.typeName;
            }
            this.getUid = function () {
                return this.uid;
            }
            this.getDevicePropertyArray = function () {
                return this.devicePropertyArray;
            }
        },
        createDevicePropertyNode = function () {
            this.name = null;
            this.value = null;
            this.getName = function () {
                return this.name;
            }
            this.getValue = function () {
                return this.value;
            }
        },
        createIODescriptionNode = function () {
            this.typeName = null;
            this.uid = null;
            this.channel=null;
            this.IOPropertyArray = [];
            this.RTDataTransferPriority = null;
            this.getTypeName = function () {
                return this.typeName;
            }
            this.getUid = function () {
                return this.uid;
            }
            this.getChannel=function(){
                return this.channel;
            }
            this.getIOPropertyArray = function () {
                return this.IOPropertyArray;
            }
            this.getRTDataTransferPriority = function () {
                return this.RTDataTransferPriority;
            }
        },
        createIOPropertyNode = function () {
            this.name = null;
            this.value = null;
            this.getName = function () {
                return this.name;
            }
            this.getValue = function () {
                return this.value;
            }
        },
        createRTTransferNode = function () {
            this.deviceUid = null;
            this.sendDataPriority = null;
            this.sendDataBlockSize = null;
            this.receiveDataPriority = null;
            this.receiveDataBlockSize = null;
            this.getDeviceUid = function () {
                return this.deviceUid;
            }
            this.getSendDataPriority = function () {
                return this.sendDataPriority;
            }
            this.getSendDataBlockSize = function () {
                return this.sendDataBlockSize;
            }
            this.getReceiveDataPriority = function () {
                return this.receiveDataPriority;
            }
            this.getReceiveDataBlockSize = function () {
                return this.receiveDataBlockSize;
            }
        },
        createDeviceSymbol = function () {
            this.uid = null;
        },
        createIOSymbolNode = function () {
            this.type = null;
            this.name = null;
            this.uid = null;
            this.channel=null;
        },
        createRTTransferArray = function(){
            this.RTTransferArray=[];
            this.getRTTransferArray=function(){
                return this.RTTransferArray;
            }
        },
        RTTransferArray=[],
        RTTransferArrayHistory=[],
        IOSymbolArray = [];
    var createNewDataForm = function (deviceSymbol, IOSymbolList) {
        var dataForm = new createDataForm;
        var deviceDescription = new createDeviceDescription;
        for (var i = 0; i < createModel.deviceArray.length; i++) {
            if (deviceSymbol.uid === createModel.deviceArray[i].getUid()) {
                deviceDescription.typeName = createModel.deviceArray[i].getType();
                deviceDescription.uid = createModel.deviceArray[i].getUid();
                var devicePropertyNode = new createDevicePropertyNode;
                devicePropertyNode.name ="model";
                devicePropertyNode.value = createModel.deviceArray[i].getModel();
                deviceDescription.devicePropertyArray.push(devicePropertyNode);
                var devicePropertyNode = new createDevicePropertyNode;
                devicePropertyNode.name ="dataSize";
                devicePropertyNode.value = createModel.deviceArray[i].getDataSize();
                deviceDescription.devicePropertyArray.push(devicePropertyNode);
                for (var j = 0; j < createModel.deviceArray[i].getDescription().length; j++) {
                    var devicePropertyNode = new createDevicePropertyNode;
                    devicePropertyNode.name = createModel.deviceArray[i].getDescription()[j].getName();
                    devicePropertyNode.value = createModel.deviceArray[i].getDescription()[j].getValue();
                    deviceDescription.devicePropertyArray.push(devicePropertyNode);
                }
                dataForm.deviceDescription = deviceDescription;
                break;
            }
        }
        for (var i = 0; i < IOSymbolList.length; i++) {
            console.log("IOSymbolList.length:"+IOSymbolList.length);
            var IOType = IOSymbolList[i].type;
            if (IOType === "bus") {
                console.log('in BUS');
                var IODescriptionNode = new createIODescriptionNode;
                for (var j = 0; j < createModel.busArray.length; j++) {
                    if(IOSymbolList[i].channel!=undefined) {
                        if (createModel.busArray[j].getUid() === IOSymbolList[i].uid && createModel.busArray[j].getType() === IOSymbolList[i].name&&
                            createModel.busArray[j].getSubAddr()===IOSymbolList[i].channel) {
                            IODescriptionNode.typeName = createModel.busArray[j].getType();
                            IODescriptionNode.uid = createModel.busArray[j].getUid();
                            IODescriptionNode.channel = createModel.busArray[j].getSubAddr();
                            for (var k = 0; k < createModel.busArray[j].getDescription().length; k++) {
                                var IOPropertyNode = new createIOPropertyNode;
                                IOPropertyNode.name = createModel.busArray[j].getDescription()[k].getName();
                                IOPropertyNode.value = createModel.busArray[j].getDescription()[k].getValue();
                                IODescriptionNode.IOPropertyArray.push(IOPropertyNode);
                            }
                        }
                    }
                    else{
                        if (createModel.busArray[j].getUid() === IOSymbolList[i].uid && createModel.busArray[j].getType() === IOSymbolList[i].name) {
                            IODescriptionNode.typeName = createModel.busArray[j].getType();
                            IODescriptionNode.uid = createModel.busArray[j].getUid();
                            for (var k = 0; k < createModel.busArray[j].getDescription().length; k++) {
                                var IOPropertyNode = new createIOPropertyNode;
                                IOPropertyNode.name = createModel.busArray[j].getDescription()[k].getName();
                                IOPropertyNode.value = createModel.busArray[j].getDescription()[k].getValue();
                                IODescriptionNode.IOPropertyArray.push(IOPropertyNode);
                            }
                        }
                    }
                }
                dataForm.IODescriptionArray.push(IODescriptionNode);
            }
            else if (IOType === "RT") {
                console.log('in RT');
                var IODescriptionNode = new createIODescriptionNode;
                for (var j = 0; j < createModel.RTArray.length; j++) {
                    if (createModel.RTArray[j].getUid() === IOSymbolList[i].uid && createModel.RTArray[j].getType() === IOSymbolList[i].name) {
                        IODescriptionNode.typeName = createModel.RTArray[j].getType();
                        IODescriptionNode.uid = createModel.RTArray[j].getUid();
                        for (var k = 0; k < createModel.RTArray[j].getDescription().length; k++) {
                            var IOPropertyNode = new createIOPropertyNode;
                            IOPropertyNode.name = createModel.RTArray[j].getDescription()[k].getName();
                            IOPropertyNode.value = createModel.RTArray[j].getDescription()[k].getValue();
                            IODescriptionNode.IOPropertyArray.push(IOPropertyNode);
                        }
                        //额外操作,数据块优先级和大小
                        for (var k = 0; k < RTTransferArray.length; k++) {
                            if (RTTransferArray[k].getDeviceUid() === deviceSymbol.uid) {
                                IODescriptionNode.RTDataTransferPriority = RTTransferArray[k];
                            }
                        }
                    }
                }
                dataForm.IODescriptionArray.push(IODescriptionNode);
            }
            else if (IOType === "deviceIO") {
                console.log('in deviceIO');
                var IODescriptionNode = new createIODescriptionNode;
                for (var j = 0; j < createModel.deviceIOArray.length; j++) {
                    if (createModel.deviceIOArray[j].getUid() === IOSymbolList[i].uid && createModel.deviceIOArray[j].getType() === IOSymbolList[i].name) {
                        IODescriptionNode.typeName = createModel.deviceIOArray[j].getType();
                        IODescriptionNode.uid = createModel.deviceIOArray[j].getUid();
                        for (var k = 0; k < createModel.deviceIOArray[j].getDescription().length; k++) {
                            var IOPropertyNode = new createIOPropertyNode;
                            IOPropertyNode.name = createModel.deviceIOArray[j].getDescription()[k].getName();
                            IOPropertyNode.value = createModel.deviceIOArray[j].getDescription[k].getValue();
                            IODescriptionNode.IOPropertyArray.push(IOPropertyNode);
                        }
                    }
                }
                dataForm.IODescriptionArray.push(IODescriptionNode);
            }
        }
        return dataForm;

        console.log('create new data form success');
    }
    var clearDataFormArray = function () {
        dataFormArray.splice(0);
    }
    var clearDataFormArrayHistory=function(){
        dataFormArrayHistory.splice(0);
    }
    var clearRTTransferArray=function(){
        RTTransferArray.splice(0);
    }
    var clearIOSymbolArray=function(){
        IOSymbolArray.splice(0);
    }
    var checkDataFormArrayContent = function (location, dataFormNumber) {
        var dataFormArray = dataFormArrayHistory[location].getDataFormArray();
        for (var i = 0; i < dataFormNumber; i++) {
          var dataForm=dataFormArray[i];
            var deviceDescription=dataForm.getDeviceDescription();
            var IODescriptionArray=dataForm.getIODescriptionArray();
            var deviceTypeName=deviceDescription.getTypeName();
            var deviceUid=deviceDescription.getUid();
            console.log(deviceTypeName+" "+deviceUid);
            var devicePropertyArray=deviceDescription.getDevicePropertyArray();
            for(var j=0;j<devicePropertyArray.length;j++){
                var name=devicePropertyArray[j].getName();
                var value=devicePropertyArray[j].getValue();
                console.log(name+": "+value);
            }
            for(var j=0;j<IODescriptionArray.length;j++){
                var IODescription=IODescriptionArray[j];
                var IOTypeName=IODescription.getTypeName();
                var IOUid=IODescription.getUid();
                console.log(IOTypeName+" "+IOUid);
                var IOPropertyArray=IODescription.getIOPropertyArray();
                for(var k=0;k<IOPropertyArray.length;k++){
                    var name=IOPropertyArray[k].getName();
                    var value=IOPropertyArray[k].getValue();
                    console.log(name+": "+value);
                }
                if(IOTypeName==="RT"){
                    var RTProperty=IODescription.getRTDataTransferPriority();
                    var sp=RTProperty.getSendDataPriority();
                    var sb=RTProperty.getSendDataBlockSize();
                    var rp=RTProperty.getReceiveDataPriority();
                    var rb=RTProperty.getReceiveDataBlockSize();
                    console.log("sp:"+sp);
                    console.log("sb:"+sb);
                    console.log("rp:"+rp);
                    console.log("rb:"+rb);
                }
            }
        }
    }
    return {
        createNewDataForm: createNewDataForm,
        dataFormArray: dataFormArray,
        createDeviceSymbol: createDeviceSymbol,
        createIOSymbolNode: createIOSymbolNode,
        IOSymbolArray: IOSymbolArray,
        createRTTransferNode: createRTTransferNode,
        createRTTransferArray: createRTTransferArray,
        dataFormArrayHistory: dataFormArrayHistory,
        clearDataFormArray: clearDataFormArray,
        checkDataFormArrayContent: checkDataFormArrayContent,
        clearDataFormArrayHistory:clearDataFormArrayHistory,
        clearRTTransferArray:clearRTTransferArray,
        clearIOSymbolArray:clearIOSymbolArray,
        RTTransferArrayHistory:RTTransferArrayHistory,
        RTTransferArray: RTTransferArray,
        createDataFormArray:createDataFormArray
    }

});