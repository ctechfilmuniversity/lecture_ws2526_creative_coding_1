import type { DiceType } from './diceGeometries';

export interface UIHandlers {
  onRoll: (type: DiceType) => void;
}

let resultDisplay: HTMLDivElement | null = null;
let currentDiceType: DiceType = 'd6';

export function setupUI(handlers: UIHandlers): void {
  const button = document.getElementById('roll-button') as HTMLButtonElement;
  resultDisplay = document.getElementById('result-display') as HTMLDivElement;

  const selectedDiv = document.getElementById('dice-selected') as HTMLDivElement;
  const optionsContainer = document.getElementById('dice-options') as HTMLDivElement;
  const options = optionsContainer.querySelectorAll('div');

  selectedDiv.addEventListener('click', (e) => {
    e.stopPropagation();
    optionsContainer.classList.toggle('select-hide');
  });

  options.forEach(option => {
    option.addEventListener('click', (e) => {
      e.stopPropagation();
      const val = option.getAttribute('data-value') as DiceType;
      currentDiceType = val;
      selectedDiv.textContent = val;
      
      options.forEach(opt => opt.classList.remove('same-as-selected'));
      option.classList.add('same-as-selected');
      
      optionsContainer.classList.add('select-hide');
    });
  });

  document.addEventListener('click', () => {
    optionsContainer.classList.add('select-hide');
  });

  button.addEventListener('click', () => {
    handlers.onRoll(currentDiceType);
  });
}

export function showResult(result: number | null): void {
  if (resultDisplay) {
    resultDisplay.textContent = result === null ? '' : result.toString();
  }
}