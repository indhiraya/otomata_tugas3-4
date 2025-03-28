
import json
def mealy_machine_simulation(data):
    states = data["states"]
    transitions = data["transitions"]
    initial_state = data["initial_state"]
    input_sequence = input("Input Sequence: ")
    current_state = initial_state
    state_path = [current_state]
    output_sequence = []
    for symbol in input_sequence:
        transition = transitions[current_state].get(str(symbol))
        if transition:
            current_state = transition["next_state"]
            output_sequence.append(transition["output"])
            state_path.append(current_state)
        else:
            print(f"Error: Tidak ada transisi untuk state {current_state} dengan input {symbol}")
            return
    print("Path:", " -> ".join(state_path))
    print("Output:", " -> ".join(output_sequence))
json_config = '''{
    "states": ["q0", "q1", "q2"],
    "transitions": {
        "q0": {"0": {"next_state": "q1", "output": "A"}, "1": {"next_state": "q2", "output": "B"}},
        "q1": {"0": {"next_state": "q0", "output": "B"}, "1": {"next_state": "q2", "output": "C"}},
        "q2": {"0": {"next_state": "q1", "output": "C"}, "1": {"next_state": "q0", "output": "A"}}
    },
    "initial_state": "q0"
}'''
mealy_machine_simulation(json.loads(json_config))