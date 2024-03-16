const BASE_PATH = "http://localhost:8080"

document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("controllerForm").addEventListener("submit", e => {
        e.preventDefault()
        sendData("SET", document.getElementById("valveLevelInput").value, -1, "")
        setTimeout(() => location.reload(), 200);
    })

    document.getElementById("controlTypeInput").addEventListener("change", function() {
        if (this.value === "auto") {
            window.alert("You have successfully changed the control type to automatic. The system will now be controlled by the water level sensor.");
            sendData("SWITCH_TO_AUTO", -1, -1, "");
        }
        document.getElementById("controllerContainer").style.display = (this.value == "auto") ? "none" : "block";
    });

    // Fetch the data
    fetch(BASE_PATH + "/api/data", {
        method: 'GET',
        mode: 'cors'
    })
    .then(res => res.json())
    .then(data => data.filter(el => el.controlType == "DATA"))
    .then(data => {
        plotDataHistory(data, document.getElementById('waterLevelTrend'));
        document.getElementById('systemState').innerHTML = "State of System: " + data[0].state;
        document.getElementById('valveValue').innerHTML = "Valve Opening Level: " + data[0].valveLevel;
    })
    .catch(error => {
        console.error('There was a problem with the fetch operation:', error);
    });
    document.getElementById("controllerContainer").style.display = (document.getElementById("controlTypeInput").value == "auto") ? "none" : "block";
    setTimeout(() => location.reload(), 10000);
})

const plotDataHistory = (data, ctx) => {
    const xValues = data.map(x => new Date(x.time).toLocaleString())
    const yValues = data.map(y => y.waterLevel)

    new Chart(ctx, {
        type: "line",
        data: {
            labels: xValues,
            datasets: [{
                backgroundColor: "rgba(0,0,0,1.0)",
                borderColor: "rgba(0,0,0,0.1)",
                data: yValues
            }]
        },    
        options: {
            plugins: {
                legend: {
                    display: false
                 },
            },
        }
    });
}

function sendData(controlType, valveLevel, waterLevel, state) {
    var data = {
        controlType: controlType,
        valveLevel: valveLevel,
        waterLevel: waterLevel,
        state: state
    };
    
    fetch(BASE_PATH + "/api/data", {
        method: "POST",
        mode: "cors", 
        body: JSON.stringify(data)
    })
}