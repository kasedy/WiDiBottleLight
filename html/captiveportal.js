var ws;

const STATUS_CONNECTING = 1;
const STATUS_FAILED = 2;

function p(el) {
  return el.type == 'checkbox' ? 'checked' : 'value';
};

function has(obj, prop) {
  return obj.hasOwnProperty(prop);
}

function save_wifi() {
  var inputs = $(this).parent('.form').find('input');
  var data = {};
  data.wifi = [].reduce.call(inputs, function(data, el) {
    data[el.name] = el[p(el)];
    return data;
  }, {});
  ws.send(JSON.stringify(data));
}

function processData(jsondata) {
  if (!has(jsondata, 'wifi')) {
    return;
  }

  var wifiSettings = jsondata.wifi;
  var status = wifiSettings.status;
  if (status == STATUS_CONNECTING) {

  } else if (status == STATUS_FAILED) {

  } else {
    
  }
}

$(function() {
  ws = new WebSocket("ws://" + "192.168.0.44" /*location.host*/ + "/ws");
  ws.onmessage = function(event) {
    var jsondata = JSON.parse(event.data);
    if (jsondata) {
      processData(jsondata);
    }
  }
  $('.wifi button').on('click', save_wifi);
});