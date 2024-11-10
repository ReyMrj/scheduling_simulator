// Event listener for algorithm selection
document.getElementById("algorithm").addEventListener("change", updateFormFields);

function updateFormFields() {
    const algorithm = document.getElementById("algorithm").value;
    const inputContainer = document.getElementById("algorithmSpecificInputs");
    inputContainer.innerHTML = "";

    // Add time quantum field for Round Robin
    if (algorithm === "round_robin") {
        const quantumInput = document.createElement("input");
        quantumInput.type = "number";
        quantumInput.id = "timeQuantum";
        quantumInput.placeholder = "Time Quantum";
        inputContainer.appendChild(quantumInput);
    }

    // Add priority and burst time fields
    const pidInput = document.createElement("input");
    pidInput.type = "number";
    pidInput.placeholder = "Process ID";
    pidInput.id = "pid";
    inputContainer.appendChild(pidInput);

    const burstInput = document.createElement("input");
    burstInput.type = "number";
    burstInput.placeholder = "Burst Time";
    burstInput.id = "burstTime";
    inputContainer.appendChild(burstInput);

    // Add priority field for multilevel queue
    if (algorithm === "multilevel_queue") {
        const priorityInput = document.createElement("input");
        priorityInput.type = "number";
        priorityInput.placeholder = "Priority";
        priorityInput.id = "priority";
        inputContainer.appendChild(priorityInput);
    }
}

// Function to start the simulation
function startSimulation() {
    const algorithm = document.getElementById("algorithm").value;
    const pid = document.getElementById("pid").value;
    const burstTime = document.getElementById("burstTime").value;
    const timeQuantum = document.getElementById("timeQuantum") ? document.getElementById("timeQuantum").value : null;
    const priority = document.getElementById("priority") ? document.getElementById("priority").value : null;

    // Example of process data structure to be passed to the backend
    const process = {
        algorithm,
        pid: parseInt(pid),
        burstTime: parseInt(burstTime),
        timeQuantum: timeQuantum ? parseInt(timeQuantum) : undefined,
        priority: priority ? parseInt(priority) : undefined
    };

    // Send data to the backend to simulate scheduling (backend code will handle this)
    // For this demo, we're simulating by generating dummy data
    const simulationResult = runSimulation(process);
    drawGanttChart(simulationResult);
}

// Example simulation function to generate dummy scheduling results
function runSimulation(process) {
    // In a real-world app, you'd send `process` data to the backend to get the actual scheduling result.
    // Here, we'll just generate mock data to demonstrate visualization.
    return [
        { pid: process.pid, startTime: 0, endTime: process.burstTime }
    ];
}

// Function to render the Gantt chart
function drawGanttChart(schedulingResult) {
    const canvas = document.getElementById("ganttChart");
    const ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    schedulingResult.forEach((proc, index) => {
        const color = getRandomColor();
        const x = proc.startTime * 10; // Scaling time units for visualization
        const width = (proc.endTime - proc.startTime) * 10;
        const y = index * 30;
        const height = 20;

        ctx.fillStyle = color;
        ctx.fillRect(x, y, width, height);
        ctx.strokeRect(x, y, width, height);
        ctx.fillText(`P${proc.pid}`, x + width / 2, y + height / 2);
    });
}

// Utility to generate random colors for Gantt chart blocks
function getRandomColor() {
    return "#" + Math.floor(Math.random() * 16777215).toString(16);
}
