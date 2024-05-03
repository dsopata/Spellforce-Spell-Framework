#include <string>
#include <windows.h>
#include "../api/sf_spells.h"
#include "../api/sfsf.h"

SpellforceSpellFramework *pSpellforceSpellFramework;

// Spell index is the ID for the TYPE of spell being cast
// Spell Job is the ID for the LOGIC handler that the spell uses when being cast. ~@UnSchtalch please correct if wrong 

void __thiscall icestrike_handler(SF_CGdSpell * _this, uint16_t spell_index) {
	_this->active_spell_list[spell_index].spell_job = 0x8;
	pSpellforceSpellFramework->pCGdSpellFunctions->setXData(_this, spell_index, 0x05, 0);
	pSpellforceSpellFramework->pCGdSpellFunctions->setXData(_this, spell_index, 0x12, 0);
	pSpellforceSpellFramework->pCGdSpellFunctions->setXData(_this, spell_index, 0x26, 0);
  OutputDebugStringA("Spell Handled");
}

extern "C" __declspec(dllexport) void InitModule(SpellforceSpellFramework* framework) {
	pSpellforceSpellFramework = framework;
    framework->addSpellHandler(0xe, &icestrike_handler);
    framework->addSpellHandler(0xeb, &icestrike_handler);
    
    OutputDebugStringA("Module initialized successfully!");
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      /* Code path executed when DLL is loaded into a process's address space. */
      break;

    case DLL_THREAD_ATTACH:
      /* Code path executed when a new thread is created within the process. */
      break;

    case DLL_THREAD_DETACH:
      /* Code path executed when a thread within the process has exited *cleanly*. */
      break;

    case DLL_PROCESS_DETACH:
      /* Code path executed when DLL is unloaded from a process's address space. */
      break;
  }

  return TRUE;
}