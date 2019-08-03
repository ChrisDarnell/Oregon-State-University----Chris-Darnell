var apiKey = '1c53d09150bfd4041b9efa84dfbf8881';
document.addEventListener('DOMContentLoaded', bindButtons);

var openWeatherBaseUri = "http://api.openweathermap.org/data";
var openWeatherApiVersion = "2.5";
var openWeatherWeatherEndpoint = "weather";
var openWeatherUri = openWeatherBaseUri + "/" +
                     openWeatherApiVersion + "/" +
                     openWeatherWeatherEndpoint;

function bindButtons() {
    document.getElementById('weatherSubmit').addEventListener('click', function (event) {

        //Clear the page
        document.getElementById('weatherError').textContent = "";
        document.getElementById('cityName').textContent = "";
        document.getElementById('currentTemp').textContent = "";
        document.getElementById('humidity').textContent = "";


        var zip = document.getElementById('zipCode').value;
        var city = document.getElementById('city').value;
        if(zip === "" && city === "")
            return;
        else if(zip !== "" && city === "")
            getWeatherByZip(zip);
        else if(zip === "" && city !== "")
            getWeatherByCity(city);
        else
            document.getElementById('weatherError').textContent = "You cannot enter a city and a zip code";
        event.preventDefault();
    })

}

function getWeatherByZip(zipCode)
{
    var uri = openWeatherUri + "?zip=" + zipCode + ",us&APPID=" + apiKey;
    var req = new XMLHttpRequest();
    req.open("GET", uri, true);
    req.addEventListener('load', function() {
        if(req.status >= 200 && req.status < 400) {
            var result = JSON.parse(req.responseText);
            document.getElementById('cityName').textContent = result.name;
            document.getElementById('currentTemp').textContent = result.main.temp;
            document.getElementById('humidity').textContent = result.main.humidity;
        }

    });

    req.send(null);
}

function getWeatherByCity(city)
{
    var uri = openWeatherUri + "?q=" + city + ",us&APPID=" + apiKey;
    var req = new XMLHttpRequest();
    req.open("GET", uri, true);
    req.addEventListener('load', function() {
        if(req.status >= 200 && req.status < 400) {
            var result = JSON.parse(req.responseText);
            document.getElementById('cityName').textContent = result.name;
            document.getElementById('currentTemp').textContent = result.main.temp;
            document.getElementById('humidity').textContent = result.main.humidity;
        }

    });

    req.send(null);
}
