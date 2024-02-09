const BASE_PATH = "http://localhost:8080"

document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("controllerForm").addEventListener("submit", e => {
        e.preventDefault()

        const formData = new FormData()
        if (document.getElementById('controlTypeInput').value === "manual") {
            formData.append("controlType", document.getElementById('controlTypeInput').value)
            formData.append("valveValue", document.getElementById('valveLevelInput').value)

            fetch(BASE_PATH + "/api/data", {
                method: "POST",
                mode: "cors", 
                body: JSON.stringify(Object.fromEntries(formData))
            })
        } else {
            window.alert("You can't update the valve level in automatic mode");
        }
    })
})

// Fetch the data
fetch(BASE_PATH + "/api/data", {
    method: 'GET',
    mode: 'cors'
})
.then(res => res.json())
.then((data) => {
    plotDataHistory(data, document.getElementById('waterLevelTrend'));
    document.getElementById('systemState').innerHTML = "State of System: " + data[0].state;
    document.getElementById('valveValue').innerHTML = "Valve Opening Level: " + data[0].valveValue;
    document.getElementById('controlType').innerHTML = "Current Control Type: " + data[0].controlType;
})
.catch(error => {
    console.error('There was a problem with the fetch operation:', error);
});

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