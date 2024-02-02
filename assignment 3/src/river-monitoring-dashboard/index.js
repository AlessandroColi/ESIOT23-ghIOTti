const BASE_PATH = "http://localhost:3030"

// Add event listener to the form to send the valve level
document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("controllerForm").addEventListener("submit", e => {
        e.preventDefault()

        const formData = new FormData()
        formData.append("valveLevel", document.getElementById("valveLevelInput").value)
        
        fetch(BASE_PATH + "/api/room", {
            mode: "cors"
        })

    })
})

// Fetch the data
fetch(BASE_PATH + "/api/room", {mode: 'cors'}).then(res => res.json())
    .then((data) => {
        const waterLevelChart = document.getElementById('waterLevelTrend');
        const systemStateDisplay = document.getElementById('systemState');
        const valveLevelDisplay = document.getElementById('valveLevel');

        plotDataHistory(data.waterLevel, waterLevelChart);
        systemStateDisplay.innerHTML = "State of System: " + data.systemState;
        valveLevelDisplay.innerHTML = "Valve Opening Level: " + data.valveLevel;
    })

// Plot data using chart.js
const plotDataHistory = (data, ctx) => {
    const xValues = data.map(x => new Date(x.date).toLocaleString())
    const yValues = data.map(y => y.value)

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
    });
}