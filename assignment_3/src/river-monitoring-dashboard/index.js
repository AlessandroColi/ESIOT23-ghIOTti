const BASE_PATH = "http://localhost:8080"

document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("controllerForm").addEventListener("submit", e => {
        e.preventDefault()

        var data = {    //TODO: Al momento cliccando sull'invio setto il valveLevel a 0.
            controlType: "manual",
            valveLevel: document.getElementById('valveLevelInput').value,
            waterLevel: 0,
            state: "open"
        };

        console.log(JSON.stringify(data));
        
        fetch(BASE_PATH + "/api/data", {
            method: "POST",
            mode: "cors", 
            body: JSON.stringify(data)
        })

        setTimeout(() => location.reload(), 200);
    })

    document.getElementById("controlTypeInput").addEventListener("change", function() {
        if (this.value === "auto") {
            window.alert("You have successfully changed the control type to automatic. The system will now be controlled by the water level sensor.");
            var data = {
                controlType: "manual",
                valveLevel: -1,
                waterLevel: 0,
                state: "switch"
            };
            console.log(JSON.stringify(data));

            fetch(BASE_PATH + "/api/data", {
                method: "POST",
                mode: "cors", 
                body: JSON.stringify(data)
            })
        }
        document.getElementById("controllerContainer").style.display = (this.value == "auto") ? "none" : "block";
    });

    // Fetch the data
    fetch(BASE_PATH + "/api/data", {
        method: 'GET',
        mode: 'cors'
    })
    .then(res => res.json())
    .then(data => {
        plotDataHistory(data, document.getElementById('waterLevelTrend'));
        document.getElementById('systemState').innerHTML = "State of System: " + data[0].state;
        document.getElementById('valveValue').innerHTML = "Valve Opening Level: " + data[0].valveLevel;
        console.log(data);
    })
    .catch(error => {
        console.error('There was a problem with the fetch operation:', error);
    });
    const type = document.getElementById("controlTypeInput").value;
    document.getElementById("controllerContainer").style.display = (type == "auto") ? "none" : "block";
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