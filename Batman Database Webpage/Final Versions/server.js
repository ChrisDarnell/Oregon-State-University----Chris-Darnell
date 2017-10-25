var express = require('express');
var bodyParser = require('body-parser');
var mysql = require('mysql');
var pool = mysql.createPool({
	host: 'localhost',
	user: process.env.DBUSER,
	password: process.env.DBPASS,
	database: process.env.DBNAME
});

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout: 'main'});

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());
app.use(express.static('public'));

app.get('/', function(req, res) {
	res.render('home');
});

var selectTableData = function(res, table) {
  var ctx = {};
  pool.query('SELECT * FROM ' + table, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    ctx.results = rows;
    res.send(ctx);
  });
};

app.get('/true_id', function(req, res) {
  selectTableData(res, 'true_id');
});

app.get('/villain', function(req, res) {
  selectTableData(res, 'villain');
});

app.get('/special_abilities', function(req, res) {
  selectTableData(res, 'special_abilities');
});

app.get('/status', function(req, res) {
  selectTableData(res, 'status');
});

app.get('/true_id_villain', function(req, res) {
  selectTableData(res, 'true_id_villain');
});

app.get('/true_id_abilities', function(req, res) {
  selectTableData(res, 'true_id_abilities');
});

app.get('/true_id_status', function(req, res) {
  selectTableData(res, 'true_id_status');
});

app.get('/villain_abilities', function(req, res) {
  selectTableData(res, 'villain_abilities');
});

app.get('/villain_status', function(req, res) {
  selectTableData(res, 'villain_status');
});

app.post('/search_true_id_villain', function(req, res) {
  var ctx = {};
  var body = req.body;

  var queryStr = "SELECT true_id.first_name, true_id.last_name FROM true_id ";
  queryStr += 'INNER JOIN true_id_villain ON true_id.id = true_id_villain.true_id ';
  queryStr += 'INNER JOIN villain ON villain.id = true_id_villain.villain_id';
  queryStr += ' WHERE villain.pseudonym = "' + body.pseudonym + '";';

  pool.query(queryStr, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    ctx.results = rows;
    res.send(ctx);
  });
});

var generateUpdateStr = function(body, table) {
  var keys = [];
  var values = [];
  var str = '';
  for (var key in body) {
    keys.push(key);
    values.push("'" + body[key] + "'");
  }
  str += "INSERT INTO " + table;
  str += "(" + keys.join(",") + ")";
  str += " VALUES (" + values.join(",") + ");";

  return str;
};

var updateEntry = function(req, res, table) {
  var updateStr = generateUpdateStr(req.body, table);

  pool.query(updateStr, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    res.send(JSON.stringify(rows));
  });
};

app.post('/true_id', function(req, res) {
  updateEntry(req, res, 'true_id');
});

app.post('/villain', function(req, res) {
  updateEntry(req, res, 'villain');
});

app.post('/special_abilities', function(req, res) {
  updateEntry(req, res, 'special_abilities');
});

app.post('/status', function(req, res) {
  updateEntry(req, res, 'status');
});

app.post('/true_id_villain', function(req, res) {
  updateEntry(req, res, 'true_id_villain');
});

app.post('/true_id_abilities', function(req, res) {
  updateEntry(req, res, 'true_id_abilities');
});

app.post('/true_id_status', function(req, res) {
  updateEntry(req, res, 'true_id_status');
});

app.post('/villain_status', function(req, res) {
  updateEntry(req, res, 'villain_status');
});

app.post('/villain_abilities', function(req, res) {
  updateEntry(req, res, 'villain_abilities');
});

var deleteEntry = function(req, res, table) {
  var ctx = {};
  var id = req.body.id;
  pool.query('DELETE FROM ' + table + ' WHERE id = ' + id, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    ctx.results = JSON.stringify(rows);
    res.send(ctx);
  });
};

app.delete('/true_id', function(req, res) {
  deleteEntry(req, res, 'true_id');
});

app.delete('/villain', function(req, res) {
  deleteEntry(req, res, 'villain');
});

app.delete('/special_abilities', function(req, res) {
  deleteEntry(req, res, 'special_abilities');
});

app.delete('/status', function(req, res) {
  deleteEntry(req, res, 'status');
});

app.delete('/true_id_villain', function(req, res) {
  var ctx = {};
  var body = req.body;
  var true_id = body.true_id;
  var villain_id = body.villain_id;

  var queryStr = 'DELETE FROM true_id_villain WHERE true_id = ' + true_id;
  queryStr += ' AND villain_id = ' + villain_id + ';';

  pool.query(queryStr, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    ctx.results = JSON.stringify(rows);
    res.send(ctx);
  });
});

app.delete('/true_id_abilities', function(req, res) {
  var ctx = {};
  var body = req.body;
  var true_id = body.true_id;
  var ability_id = body.ability_id;

  var queryStr = 'DELETE FROM true_id_abilities WHERE true_id = ' + true_id;
  queryStr += ' AND ability_id = ' + ability_id + ';';

  pool.query(queryStr, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    ctx.results = JSON.stringify(rows);
    res.send(ctx);
  });
});

app.delete('/true_id_status', function(req, res) {
  var ctx = {};
  var body = req.body;
  var true_id = body.true_id;
  var status_id = body.status_id;

  var queryStr = 'DELETE FROM true_id_status WHERE true_id = ' + true_id;
  queryStr += ' AND status_id = ' + status_id + ';';

  pool.query(queryStr, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    ctx.results = JSON.stringify(rows);
    res.send(ctx);
  });
});

app.delete('/villain_abilities', function(req, res) {
  var ctx = {};
  var body = req.body;
  var villain_id = body.villain_id;
  var ability_id = body.ability_id;

  var queryStr = 'DELETE FROM villain_abilities WHERE villain_id = ' + villain_id;
  queryStr += ' AND ability_id = ' + ability_id + ';';

  pool.query(queryStr, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    ctx.results = JSON.stringify(rows);
    res.send(ctx);
  });
});

app.delete('/villain_status', function(req, res) {
  var ctx = {};
  var body = req.body;
  var villian_id = body.villain_id;
  var status_id = body.status_id;

  var queryStr = 'DELETE FROM villain_status WHERE villain_id = ' + villain_id;
  queryStr += ' AND status_id = ' + status_id + ';';

  pool.query(queryStr, function(err, rows, fields) {
    if (err) {
      console.log(err);
      return;
    }
    ctx.results = JSON.stringify(rows);
    res.send(ctx);
  });
});

app.use(function(req, res) {
	res.status(404);
	res.render('404');
});

app.use(function(err, req, res, next){
	console.log(err.stack);
	res.status(500);
	res.render('500');
});

app.listen(app.get('port'), function() {
	console.log('Application started on port ' + app.get('port'));
});