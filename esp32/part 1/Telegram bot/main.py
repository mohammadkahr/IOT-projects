import requests
from telegram import Update
from telegram.ext import ApplicationBuilder, CommandHandler, ContextTypes

URL = 'http:***'


async def send_req(command, update: Update):
    if command == 'on':
        try:
            with requests.Session() as s:
                s.get(URL, timeout=60)
                response = s.post(URL, data={'on_time': 500}, timeout=60)
                if response.status_code == 200:
                    await update.message.reply_text("The light is now on.")
                else:
                    await update.message.reply_text("Failed to turn on the light.")
        except requests.exceptions.RequestException as e:
            await update.message.reply_text(str(e))

    elif command == 'off':
        try:
            with requests.Session() as s:
                s.get(URL, timeout=60)
                response = s.post(URL, data={'off_time': 500}, timeout=60)
                if response.status_code == 200:
                    await update.message.reply_text("The light is now off.")
                else:
                    await update.message.reply_text("Failed to turn off the light.")
        except requests.exceptions.RequestException as e:
            await update.message.reply_text(str(e))


async def start(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await update.message.reply_text(f'Welcome to the esp controller {update.effective_user.first_name}!')


async def help(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await update.message.reply_text('Commands:\n'
                                    '/on - Turn on the light.\n'
                                    '/off - Turn off the light.\n')


async def on_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await send_req('on', update)


async def off_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await send_req('off', update)


if __name__ == '__main__':
    app = ApplicationBuilder().token("***").build()

    app.add_handler(CommandHandler("start", start))
    app.add_handler(CommandHandler("help", help))
    app.add_handler(CommandHandler("on", on_command))
    app.add_handler(CommandHandler("off", off_command))

    app.run_polling()
