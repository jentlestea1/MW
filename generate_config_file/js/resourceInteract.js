/**
 * Created by wangshaobo_ on 2017/8/7.
 */
define(function(){'use strict';
    var get_blob = function () {
        return Blob;
    };
    var loadXML=function(e,xml,projectName){
        e.preventDefault();
        var BB = get_blob();
        saveAs(
            new BB(
                [xml],
                {type: "text/plain;charset=" + document.characterSet}
            )
            , (projectName) + ".xml"
        );
    }
    var upLoadModel=function(){

    }
    return{
        loadXML:loadXML,
        uploadModel:upLoadModel
    }
});