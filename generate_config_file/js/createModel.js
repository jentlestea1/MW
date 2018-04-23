/**
 * Created by wangshaobo_ on 2017/7/29.
 */
define(function () {
    'use strict';
    var deviceArray = [],
        deviceIOArray = [],
        RTArray = [],
        busArray = [],
        cpuUnitArray = [],
        createDeviceNode = function () {
            this.uid = null,
                this.type = null,
                this.model = null,
                this.dataSize = null,
                this.description = [],
                //this.inPortArray = [],
                //this.outPortArray = [],
                this.getUid = function () {
                    return this.uid;
                },
                this.getType = function () {
                    return this.type;
                },
                this.getModel = function () {
                    return this.model;
                },
                this.getDataSize = function () {
                    return this.dataSize;
                },
                this.getDescription = function () {
                    return this.description;
                }
            //this.getOutPortArray = function () {
            //    return this.outPortArray;
            //},
            //this.getInPortArray = function () {
            //     return this.inPortArray;
            // }
        },
        createIONode = function () {
            this.uid = null,
                this.type = null,
                this.subAddr = null,
                this.description = [],
                this.getUid = function () {
                    return this.uid;
                },
                this.getType = function () {
                    return this.type;
                },
                this.getSubAddr = function () {
                    return this.subAddr;
                }
            this.getDescription = function () {
                return this.description;
            }
        },
        createCpuUnitNode = function () {
            this.uid = null,
                this.model = null,
                this.portArray = [],
                this.getUid = function () {
                    return this.uid;
                },
                this.getModel = function () {
                    return this.model;
                },
                this.getPortArray = function () {
                    return this.portArray;
                }
        },
        createPortArrayNode = function () {
            this.uid = null,
                this.name = null,
                this.supportIO = null,
                this.getUid = function () {
                    return this.uid;
                },
                this.getName=function () {
                    return this.uid;
                },
                this.getSupportIO=function(){
                    return this.supportIO;
                }
        },
        createDescriptionNode = function () {
            this.name = null,
                this.value = null,
                this.getName = function () {
                    return this.name;
                },
                this.getValue = function () {
                    return this.value;
                }

        };
    /*
     var createImgModel=function(type){//获取pX,pY，创建一个svg图标

     }
     var onMouseMove=function(){

     }
     var mouseUp=function(){
     }
     */

    var createNewDeviceModel = function (uid, type, model, dataSize, description) {
        var deviceNode = new createDeviceNode();
        deviceNode.uid = uid;
        deviceNode.type = type;
        deviceNode.model = model;
        deviceNode.dataSize = dataSize;
        for (var i = 0; i < description.length; i++) {
            deviceNode.description.push(description[i]);
        }
        deviceArray.push(deviceNode);
        console.log(JSON.stringify(deviceArray));
        console.log('create new device model success');
    }
    var reviseDeviceModel = function (uid) {
    }
    var deleteDeviceModel = function (uid) {
        var pos = null;
        for (var i = 0; i < deviceArray.length; i++) {
            if (deviceArray[i].uid === uid) {
                pos = i;
                break;
            }
        }
        deviceArray.splice(pos, 1);
        console.log('delete DeviceModel success');
    }
    var createNewIOModel = function (uid, type, subAddr, description) {
        var IONode = new createIONode();
        IONode.uid = uid;
        IONode.type = type;
        IONode.subAddr = subAddr;
        IONode.description = description;
        if (type === "RT") {
            RTArray.push(IONode);
        }
        else if (type === "ad" || type === "da") {
            deviceIOArray.push(IONode);
        }
        else {
            busArray.push(IONode);
        }
        console.log(JSON.stringify(busArray));
        console.log('create new IO model success');
    }
    var reviseIOModel = function () {

    }
    var deleteIOModel = function (subType, uid) {
        var pos = -1;
        if (subType === 'RT') {
            for (var i = 0; i < RTArray.length; i++) {
                if (RTArray[i].getUid() === uid) {
                    pos = i;
                    break;
                }
            }
            RTArray.splice(pos, 1);
        }

        else {
            for (var i = 0; i < busArray.length; i++) {
                if (busArray[i].getUid() === uid && busArray[i].getType() === subType) {
                    pos = i;
                    break;
                }
            }
            //console.log(pos);
            //console.log(subType+"|"+uid);
            if (pos != -1) {
                busArray.splice(pos, 1);
            }
            else {
                for (var i = 0; i < deviceIOArray.length; i++) {
                    if (deviceIOArray[i].getUid() === uid && deviceIOArray[i].getType() === subType) {
                        pos = i;
                        break;
                    }
                }
                deviceIOArray.splice(pos, 1);
            }
        }


        console.log('delete IOModel success');
    }
    var createNewCpuUnitModel = function (uid, model, portArray) {
        var cpuUnitNode = new createCpuUnitNode;
        cpuUnitNode.uid = uid;
        cpuUnitNode.model = model;
        for (var i = 0; i < portArray.length; i++) {
            cpuUnitNode.portArray[i] = portArray[i];
        }
        cpuUnitArray.push(cpuUnitNode);
        console.log(JSON.stringify(cpuUnitArray));
    }
    var deleteCpuUnitModel=function(uid){
        var pos = null;
        for (var i = 0; i < cpuUnitArray.length; i++) {
            if (cpuUnitArray[i].uid === uid) {
                pos = i;
                break;
            }
        }
        cpuUnitArray.splice(pos, 1);
        console.log('delete cpuUnitModel success');
    }
    return {
        deviceArray: deviceArray,
        deviceIOArray: deviceIOArray,
        RTArray: RTArray,
        busArray: busArray,
        cpuUnitArray: cpuUnitArray,
        createDescriptionNode: createDescriptionNode,
        createPortArrayNode:createPortArrayNode,
        createNewDeviceModel: createNewDeviceModel,
        reviseDeviceModel: reviseDeviceModel,
        createNewIOModel: createNewIOModel,
        reviseIOModel: reviseIOModel,
        deleteDeviceModel: deleteDeviceModel,
        deleteIOModel: deleteIOModel,
        createNewCpuUnitModel:createNewCpuUnitModel,
        deleteCpuUnitModel:deleteCpuUnitModel
    }

});