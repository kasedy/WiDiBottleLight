function p(el) {
  return el.type == 'checkbox' ? 'checked' : 'value';
};
var ws = new WebSocket("ws://" + "192.168.0.44" /*location.host*/ + "/ws"),
  form = document.forms[0];
form.onchange = function() {
  ws.send(JSON.stringify([].reduce.call(form, function(data, el) {
    data[el.name] = el[p(el)];
    return data;
  }, {})));
};
ws.onmessage = function(event) {
  var jsondata = JSON.parse(event.data);
  var selectOptions = jsondata.options;
  [].forEach.call(form, function(el) {
    if (selectOptions.hasOwnProperty(el.name)) {
      el.innerHTML = '';
      var options = selectOptions[el.name];
      for (option in options) {
        el.append(new Option(options[option], option));
      }
    }
    if (jsondata.hasOwnProperty(el.name)) {
      el[p(el)] = jsondata[el.name];
    }
  });
}