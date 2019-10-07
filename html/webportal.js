function p(el) {
  return el.type == 'checkbox' ? 'checked' : 'value';
};
var ip = new URL(location.href).searchParams.get('ip') || location.host;
var ws = new WebSocket("ws://" + ip + "/ws"),
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