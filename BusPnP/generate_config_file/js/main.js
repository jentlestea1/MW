/**
 * Created by wangshaobo_ on 2017/8/2.
 */
(function(){'use strict'
    require.config({
        baseUrl:'./',
    });
    require(['js/views'],function(views){
        $(document).ready(function(){
            views.viewInit();
        });
    });
}());