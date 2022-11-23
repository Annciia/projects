using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using OrganizerNotatek.Infrastructure.Services;
using OrganizerNotatek.Infrastructure.DTO;

namespace OrganizerNotatek.API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class NotesController : ControllerBase
    {
        private readonly INoteService _noteService;
        public NotesController(INoteService noteService)
        {
            _noteService = noteService;
        }

        [HttpGet]
        public IActionResult Get()
        {
            var notes = _noteService.GetAll();

            return Ok(notes);
        }

        [HttpGet("id")]
        public IActionResult Get(Guid id)
        {
            var note = _noteService.Get(id);
            if (note == null)
            {
                return NotFound();
            }

            return Ok(note);
        }

        [HttpPost]
        public IActionResult Post([FromBody] NoteDTO note) 
        {
            var newID = Guid.NewGuid();
            note = _noteService.Create(newID, note.Title, note.Content);
            return Created($"api/notes.{newID}",note);
        }

        [HttpPut("id")]
        public IActionResult Put(Guid id, [FromBody] NoteDTO note)
        {
            note = _noteService.Update(id, note.Title, note.Content);

            if (note == null)
            {
                return NotFound();
            }

            return Ok(note);
        }

        [HttpDelete("id")]
        public IActionResult Delete(Guid id)
        {
            _noteService.Delete(id);
            return NoContent();
        }

    }
}
